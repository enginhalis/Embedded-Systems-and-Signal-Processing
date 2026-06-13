#ifndef SCENARIO_H
#define SCENARIO_H

#include "imu_types.h"

void inject_packet(Scenario sc,
                   uint32_t time_ms,
                   PacketQueue *q,
                   DelaySlot *delay,
                   const Packet *packet,
                   Stats *stats);

void release_delayed_if_ready(uint32_t time_ms,
                              PacketQueue *q,
                              DelaySlot *delay,
                              Stats *stats);

void print_header(Scenario sc);
void print_sample_summary(const SampleView *s, int q_count);
void print_sample_detail(const SampleView *s, int q_count);
void print_stats(Scenario sc, const Stats *st);
void run_scenario(Scenario sc);

#endif
