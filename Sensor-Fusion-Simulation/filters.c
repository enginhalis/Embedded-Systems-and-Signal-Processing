#include "filters.h"

#include <string.h>
#include <math.h>

void avg_init(AvgFilter *f) {
    memset(f, 0, sizeof(*f));
}

double avg_apply(AvgFilter *f, double x) {
    f->sum -= f->buf[f->index];
    f->buf[f->index] = x;
    f->sum += x;

    f->index = (f->index + 1) % MA_WINDOW;

    if (f->count < MA_WINDOW) {
        f->count++;
    }

    return f->sum / (double)f->count;
}

void lpf_init(LowPassFilter *f) {
    f->prev = 0.0;
    f->ready = false;
}

double lpf_apply(LowPassFilter *f, double x) {
    if (!f->ready) {
        f->prev = x;
        f->ready = true;
        return x;
    }

    f->prev = LPF_ALPHA * x + (1.0 - LPF_ALPHA) * f->prev;
    return f->prev;
}

void filters_init(FilterSet *f) {
    avg_init(&f->ax);
    avg_init(&f->ay);
    avg_init(&f->az);

    lpf_init(&f->gx);
    lpf_init(&f->gy);
    lpf_init(&f->gz);

    f->gyro_roll = 0.0;
    f->gyro_pitch = 0.0;
    f->gyro_yaw = 0.0;
    f->gyro_ready = false;

    f->comp_roll = 0.0;
    f->comp_pitch = 0.0;
    f->comp_ready = false;
}

ImuData apply_filters(FilterSet *f, const ImuData *in) {
    ImuData out;

    /* İvmeölçer verisi daha dalgalı olduğu için moving average kullandım */
    out.ax = avg_apply(&f->ax, in->ax);
    out.ay = avg_apply(&f->ay, in->ay);
    out.az = avg_apply(&f->az, in->az);

    /* Jiroskopta ani sıçramaları yumuşatmak için low-pass kullandım */
    out.gx = lpf_apply(&f->gx, in->gx);
    out.gy = lpf_apply(&f->gy, in->gy);
    out.gz = lpf_apply(&f->gz, in->gz);

    return out;
}

Angle2D calc_acc_angle(const ImuData *imu) {
    Angle2D a;

    /*
       İvmeölçer sadece yerçekimine duyarlı olduğu için
       roll ve pitch hesaplanabilir, yaw hesaplanamaz.
    */
    a.roll  = RAD2DEG(atan2(imu->ay, imu->az));
    a.pitch = RAD2DEG(atan2(-imu->ax, sqrt(imu->ay * imu->ay + imu->az * imu->az)));

    return a;
}

Pose update_gyro_integrated(FilterSet *f, const ImuData *imu, const Angle2D *acc) {
    Pose p;

    if (!f->gyro_ready) {
        f->gyro_roll = acc->roll;
        f->gyro_pitch = acc->pitch;
        f->gyro_yaw = 0.0;
        f->gyro_ready = true;
    } else {
        f->gyro_roll  += RAD2DEG(imu->gx) * DT_SEC;
        f->gyro_pitch += RAD2DEG(imu->gy) * DT_SEC;
        f->gyro_yaw   += RAD2DEG(imu->gz) * DT_SEC;
    }

    p.roll = f->gyro_roll;
    p.pitch = f->gyro_pitch;
    p.yaw = f->gyro_yaw;

    return p;
}

/*
   Complementary filter ile roll ve pitch hesaplanıyor.

   İvmeölçer yerçekimine göre referans verir (uzun vadede doğru),
   jiroskop ise kısa vadede hızlı değişimleri yakalar.

   Not:
   Yaw açısı burada hesaplanmadı.
   Çünkü yalnızca ivmeölçer + jiroskop kullanıldığında yaw için
   sabit bir referans yoktur ve gyro entegrasyonu zamanla drift oluşturur.
   Yaw hesaplamak için magnetometre (pusula) verisi gerekir.
*/
Angle2D update_complementary(FilterSet *f, const ImuData *imu, const Angle2D *acc) {
    Angle2D c;

    if (!f->comp_ready) {
        f->comp_roll = acc->roll;
        f->comp_pitch = acc->pitch;
        f->comp_ready = true;
    } else {
        f->comp_roll =
            COMP_ALPHA * (f->comp_roll + RAD2DEG(imu->gx) * DT_SEC) +
            (1.0 - COMP_ALPHA) * acc->roll;

        f->comp_pitch =
            COMP_ALPHA * (f->comp_pitch + RAD2DEG(imu->gy) * DT_SEC) +
            (1.0 - COMP_ALPHA) * acc->pitch;
    }

    c.roll = f->comp_roll;
    c.pitch = f->comp_pitch;

    return c;
}
