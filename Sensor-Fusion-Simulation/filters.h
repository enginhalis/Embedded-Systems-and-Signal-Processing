#ifndef FILTERS_H
#define FILTERS_H

#include "imu_types.h"

void avg_init(AvgFilter *f);
double avg_apply(AvgFilter *f, double x);

void lpf_init(LowPassFilter *f);
double lpf_apply(LowPassFilter *f, double x);

void filters_init(FilterSet *f);
ImuData apply_filters(FilterSet *f, const ImuData *in);
Angle2D calc_acc_angle(const ImuData *imu);
Pose update_gyro_integrated(FilterSet *f, const ImuData *imu, const Angle2D *acc);
Angle2D update_complementary(FilterSet *f, const ImuData *imu, const Angle2D *acc);

#endif
