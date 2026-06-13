#include "scenario.h"
#include "imu_utils.h"
#include "imu_sim.h"
#include "packet.h"
#include "filters.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

void inject_packet(Scenario sc,
                   uint32_t time_ms,
                   PacketQueue *q,
                   DelaySlot *delay,
                   const Packet *packet,
                   Stats *stats) {
    bool push_ok;

    stats->generated++;

    switch (sc) {
        case SC_PACKET_LOSS:
            if ((time_ms % 1000) == 300) {
                stats->lost++;
                return;
            }
            break;

        case SC_CORRUPT_PACKET: {
            Packet temp = *packet;

            if ((time_ms % 1000) == 500) {
                temp.bytes[10] ^= 0x5A;
                stats->corrupted++;
            }

            push_ok = queue_push(q, &temp);
            if (!push_ok) {
                stats->overflows++;
            } else {
                stats->injected++;
            }
            return;
        }

        case SC_DELAYED_PACKET:
            if ((time_ms % 1000) == 700 && !delay->active) {
                delay->packet = *packet;
                delay->release_ms = time_ms + 200;
                delay->active = true;
                stats->delayed++;
                return;
            }
            break;

        case SC_NORMAL:
        default:
            break;
    }

    push_ok = queue_push(q, packet);
    if (!push_ok) {
        stats->overflows++;
    } else {
        stats->injected++;
    }
}

void release_delayed_if_ready(uint32_t time_ms,
                              PacketQueue *q,
                              DelaySlot *delay,
                              Stats *stats) {
    bool push_ok;

    if (!delay->active) {
        return;
    }

    if (time_ms >= delay->release_ms) {
        push_ok = queue_push(q, &delay->packet);

        if (!push_ok) {
            stats->overflows++;
        } else {
            stats->injected++;
        }

        delay->active = false;
    }
}

void print_header(Scenario sc) {
    printf("\n============================== %s ==============================\n",
           scenario_name(sc));
    printf("  Time |  Seq | Status    | Ideal(R,P)          | Comp(R,P)           | Proc(us) | Q\n");
    printf("--------------------------------------------------------------------------------------\n");
}

void print_sample_summary(const SampleView *s, int q_count) {
    printf("%6u | %4u | %-9s | (%7.2f, %7.2f) | (%7.2f, %7.2f) | %8.3f | %d\n",
           s->time_ms,
           s->seq,
           status_name(s->status),
           s->ideal.roll,
           s->ideal.pitch,
           s->comp_angle.roll,
           s->comp_angle.pitch,
           s->proc_us,
           q_count);
}

void print_sample_detail(const SampleView *s, int q_count) {
    printf("\n[DETAIL @ %u ms] Seq=%u  Status=%s  Q=%d\n",
           s->time_ms, s->seq, status_name(s->status), q_count);

    printf("  Ideal          : Roll=%8.2f  Pitch=%8.2f  Yaw=%8.2f deg\n",
           s->ideal.roll, s->ideal.pitch, s->ideal.yaw);

    printf("  Comp Angle     : Roll=%8.2f  Pitch=%8.2f deg\n",
           s->comp_angle.roll, s->comp_angle.pitch);

    printf("  Gyro Int Angle : Roll=%8.2f  Pitch=%8.2f  Yaw=%8.2f deg\n",
           s->gyro_int_angle.roll, s->gyro_int_angle.pitch, s->gyro_int_angle.yaw);

    printf("  Acc Angle      : Roll=%8.2f  Pitch=%8.2f deg\n",
           s->acc_angle.roll, s->acc_angle.pitch);

    printf("  Raw Acc        : X=%6d  Y=%6d  Z=%6d\n",
           s->raw.ax, s->raw.ay, s->raw.az);

    printf("  Raw Gyro       : X=%6d  Y=%6d  Z=%6d\n",
           s->raw.gx, s->raw.gy, s->raw.gz);

    printf("  Physical Acc   : X=%8.3f  Y=%8.3f  Z=%8.3f m/s^2\n",
           s->physical.ax, s->physical.ay, s->physical.az);

    printf("  Physical Gyro  : X=%8.3f  Y=%8.3f  Z=%8.3f deg/s\n",
           RAD2DEG(s->physical.gx), RAD2DEG(s->physical.gy), RAD2DEG(s->physical.gz));

    printf("  Filtered Acc   : X=%8.3f  Y=%8.3f  Z=%8.3f m/s^2\n",
           s->filtered.ax, s->filtered.ay, s->filtered.az);

    printf("  Filtered Gyro  : X=%8.3f  Y=%8.3f  Z=%8.3f deg/s\n",
           RAD2DEG(s->filtered.gx), RAD2DEG(s->filtered.gy), RAD2DEG(s->filtered.gz));
}

void print_stats(Scenario sc, const Stats *st) {
    double avg_proc = 0.0;
    double roll_rmse = 0.0;
    double pitch_rmse = 0.0;

    if (st->processed > 0) {
        avg_proc = st->total_proc_us / (double)st->processed;
    }

    if (st->valid_angle_count > 0) {
        roll_rmse = sqrt(st->roll_sq_err / (double)st->valid_angle_count);
        pitch_rmse = sqrt(st->pitch_sq_err / (double)st->valid_angle_count);
    }

    printf("\n=========================== SCENARIO SUMMARY ===========================\n");
    printf("Scenario            : %s\n", scenario_name(sc));
    printf("Generated packets   : %zu\n", st->generated);
    printf("Injected packets    : %zu\n", st->injected);
    printf("Processed packets   : %zu\n", st->processed);
    printf("Lost packets        : %zu\n", st->lost);
    printf("Corrupted packets   : %zu\n", st->corrupted);
    printf("Delayed packets     : %zu\n", st->delayed);
    printf("Checksum errors     : %zu\n", st->checksum_errors);
    printf("Queue overflows     : %zu\n", st->overflows);
    printf("Avg proc time (us)  : %.3f\n", avg_proc);
    printf("Max proc time (us)  : %.3f\n", st->max_proc_us);
    printf("Roll RMSE (deg)     : %.3f\n", roll_rmse);
    printf("Pitch RMSE (deg)    : %.3f\n", pitch_rmse);
}

void run_scenario(Scenario sc) {
    PacketQueue rx;
    DelaySlot delay;
    FilterSet filters;
    Stats stats;

    uint16_t seq = 0;
    uint32_t time_ms;

    queue_init(&rx);
    delay.active = false;
    filters_init(&filters);
    memset(&stats, 0, sizeof(stats));

    print_header(sc);

    for (time_ms = 0; time_ms <= SIM_DURATION_MS; time_ms += SAMPLE_MS, seq++) {
        double t = (double)time_ms / 1000.0;

        ImuData ideal_imu;
        Pose ideal_pose_value;
        ImuData noisy_imu;
        RawData raw;
        Packet packet;
        Packet rx_packet;
        SampleView view;
        bool got_packet;
        double t0, t1;

        make_ideal_sample(t, &ideal_imu, &ideal_pose_value);
        noisy_imu = add_sensor_errors(t, &ideal_imu);

        raw = imu_to_raw(&noisy_imu);
        packet = make_packet(seq, time_ms, &raw);

        inject_packet(sc, time_ms, &rx, &delay, &packet, &stats);
        release_delayed_if_ready(time_ms, &rx, &delay, &stats);

        got_packet = queue_pop(&rx, &rx_packet);
        if (!got_packet) {
            continue;
        }

        memset(&view, 0, sizeof(view));
        view.status = ST_OK;

        t0 = now_us();

        if (!parse_packet(&rx_packet, &view.seq, &view.time_ms, &view.raw)) {
            view.status = ST_CHECKSUM;
            stats.checksum_errors++;

            t1 = now_us();
            view.proc_us = elapsed_us(t0, t1);

            if ((time_ms % PRINT_MS) == 0) {
                print_sample_summary(&view, rx.count);
            }
            continue;
        }

        view.ideal = ideal_pose_value;
        view.physical = raw_to_imu(&view.raw);
        view.filtered = apply_filters(&filters, &view.physical);

        view.acc_angle = calc_acc_angle(&view.filtered);
        view.gyro_int_angle = update_gyro_integrated(&filters, &view.filtered, &view.acc_angle);
        view.comp_angle = update_complementary(&filters, &view.filtered, &view.acc_angle);

        t1 = now_us();
        view.proc_us = elapsed_us(t0, t1);

        stats.processed++;
        stats.total_proc_us += view.proc_us;

        if (view.proc_us > stats.max_proc_us) {
            stats.max_proc_us = view.proc_us;
        }

        stats.roll_sq_err += (view.comp_angle.roll - view.ideal.roll) *
                             (view.comp_angle.roll - view.ideal.roll);

        stats.pitch_sq_err += (view.comp_angle.pitch - view.ideal.pitch) *
                              (view.comp_angle.pitch - view.ideal.pitch);

        stats.valid_angle_count++;

        if ((time_ms % PRINT_MS) == 0) {
            print_sample_summary(&view, rx.count);
            print_sample_detail(&view, rx.count);
        }
    }

    print_stats(sc, &stats);
}
