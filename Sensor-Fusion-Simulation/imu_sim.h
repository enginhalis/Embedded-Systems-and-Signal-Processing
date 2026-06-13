#ifndef IMU_SIM_H
#define IMU_SIM_H

#include "imu_types.h"

Pose ideal_pose(double t);
void make_ideal_sample(double t, ImuData *imu, Pose *pose);
ImuData add_sensor_errors(double t, const ImuData *ideal);

RawData imu_to_raw(const ImuData *s);
ImuData raw_to_imu(const RawData *r);

#endif
