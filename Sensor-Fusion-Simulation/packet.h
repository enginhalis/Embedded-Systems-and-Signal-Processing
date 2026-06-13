#ifndef PACKET_H
#define PACKET_H

#include "imu_types.h"

Packet make_packet(uint16_t seq, uint32_t time_ms, const RawData *raw);
bool parse_packet(const Packet *p, uint16_t *seq, uint32_t *time_ms, RawData *raw);

#endif
