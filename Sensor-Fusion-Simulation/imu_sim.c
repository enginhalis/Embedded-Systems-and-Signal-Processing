#include "imu_sim.h"
#include "imu_utils.h"

#include <math.h>

Pose ideal_pose(double t) {
    const double w = 2.0 * PI * MOTION_HZ;
    Pose p;

    p.roll  = ROLL_AMP_DEG  * sin(w * t);
    p.pitch = PITCH_AMP_DEG * sin(w * t + PI / 6.0);
    p.yaw   = YAW_AMP_DEG   * sin(w * t + PI / 4.0);

    return p;
}

void make_ideal_sample(double t, ImuData *imu, Pose *pose) {
    const double w = 2.0 * PI * MOTION_HZ;
    Pose p = ideal_pose(t);

    double roll_rad  = DEG2RAD(p.roll);
    double pitch_rad = DEG2RAD(p.pitch);

    imu->ax = -GRAVITY * sin(pitch_rad);
    imu->ay =  GRAVITY * sin(roll_rad) * cos(pitch_rad);
    imu->az =  GRAVITY * cos(roll_rad) * cos(pitch_rad);

    imu->gx = DEG2RAD(ROLL_AMP_DEG  * w * cos(w * t));
    imu->gy = DEG2RAD(PITCH_AMP_DEG * w * cos(w * t + PI / 6.0));
    imu->gz = DEG2RAD(YAW_AMP_DEG   * w * cos(w * t + PI / 4.0));

    *pose = p;
}

ImuData add_sensor_errors(double t, const ImuData *ideal) {
    ImuData noisy;

    noisy.ax = ideal->ax + rand_gauss(ACC_NOISE_SIGMA);
    noisy.ay = ideal->ay + rand_gauss(ACC_NOISE_SIGMA);
    noisy.az = ideal->az + rand_gauss(ACC_NOISE_SIGMA);

    noisy.gx = ideal->gx + DEG2RAD(GYRO_BIAS_X_DPS + GYRO_DRIFT_X_DPSPS * t + rand_gauss(GYRO_NOISE_SIGMA));
    noisy.gy = ideal->gy + DEG2RAD(GYRO_BIAS_Y_DPS + GYRO_DRIFT_Y_DPSPS * t + rand_gauss(GYRO_NOISE_SIGMA));
    noisy.gz = ideal->gz + DEG2RAD(GYRO_BIAS_Z_DPS + GYRO_DRIFT_Z_DPSPS * t + rand_gauss(GYRO_NOISE_SIGMA));

    return noisy;
}

RawData imu_to_raw(const ImuData *s) {
    RawData r;

    r.ax = clamp_i16((s->ax / GRAVITY) * ACC_LSB_PER_G);
    r.ay = clamp_i16((s->ay / GRAVITY) * ACC_LSB_PER_G);
    r.az = clamp_i16((s->az / GRAVITY) * ACC_LSB_PER_G);

    r.gx = clamp_i16(RAD2DEG(s->gx) * GYRO_LSB_PER_DPS);
    r.gy = clamp_i16(RAD2DEG(s->gy) * GYRO_LSB_PER_DPS);
    r.gz = clamp_i16(RAD2DEG(s->gz) * GYRO_LSB_PER_DPS);

    return r;
}

ImuData raw_to_imu(const RawData *r) {
    ImuData s;

    s.ax = ((double)r->ax / ACC_LSB_PER_G) * GRAVITY;
    s.ay = ((double)r->ay / ACC_LSB_PER_G) * GRAVITY;
    s.az = ((double)r->az / ACC_LSB_PER_G) * GRAVITY;

    s.gx = DEG2RAD((double)r->gx / GYRO_LSB_PER_DPS);
    s.gy = DEG2RAD((double)r->gy / GYRO_LSB_PER_DPS);
    s.gz = DEG2RAD((double)r->gz / GYRO_LSB_PER_DPS);

    return s;
}
