#ifndef IMU_UTILS_H
#define IMU_UTILS_H

#include "imu_types.h"

double now_us(void);
double elapsed_us(double start_us, double end_us);
double rand_uniform(void);
double rand_gauss(double sigma);
int16_t clamp_i16(double x);
const char *scenario_name(Scenario s);
const char *status_name(Status s);

void queue_init(PacketQueue *q);
bool queue_push(PacketQueue *q, const Packet *p);
bool queue_pop(PacketQueue *q, Packet *p);

#endif
