#include "packet.h"

static void write_u16(uint8_t *buf, int idx, uint16_t x) {
    buf[idx + 0] = (uint8_t)(x & 0xFFu);
    buf[idx + 1] = (uint8_t)((x >> 8) & 0xFFu);
}

static void write_u32(uint8_t *buf, int idx, uint32_t x) {
    buf[idx + 0] = (uint8_t)(x & 0xFFu);
    buf[idx + 1] = (uint8_t)((x >> 8) & 0xFFu);
    buf[idx + 2] = (uint8_t)((x >> 16) & 0xFFu);
    buf[idx + 3] = (uint8_t)((x >> 24) & 0xFFu);
}

static uint16_t read_u16(const uint8_t *buf, int idx) {
    return (uint16_t)(buf[idx + 0] | ((uint16_t)buf[idx + 1] << 8));
}

static uint32_t read_u32(const uint8_t *buf, int idx) {
    return ((uint32_t)buf[idx + 0]) |
           ((uint32_t)buf[idx + 1] << 8) |
           ((uint32_t)buf[idx + 2] << 16) |
           ((uint32_t)buf[idx + 3] << 24);
}

static uint8_t calc_checksum(const uint8_t *buf, int len) {
    uint8_t c = 0;
    int i;

    for (i = 0; i < len; i++) {
        c ^= buf[i];
    }

    return c;
}

Packet make_packet(uint16_t seq, uint32_t time_ms, const RawData *raw) {
    Packet p;

    p.bytes[0] = 0xAA;
    p.bytes[1] = 0x55;

    write_u16(p.bytes, 2, seq);
    write_u32(p.bytes, 4, time_ms);

    write_u16(p.bytes, 8,  (uint16_t)raw->ax);
    write_u16(p.bytes, 10, (uint16_t)raw->ay);
    write_u16(p.bytes, 12, (uint16_t)raw->az);
    write_u16(p.bytes, 14, (uint16_t)raw->gx);
    write_u16(p.bytes, 16, (uint16_t)raw->gy);
    write_u16(p.bytes, 18, (uint16_t)raw->gz);

    p.bytes[20] = 0;
    p.bytes[21] = 0;
    p.bytes[22] = 0;

    p.bytes[23] = calc_checksum(p.bytes, PACKET_SIZE - 1);

    return p;
}

bool parse_packet(const Packet *p, uint16_t *seq, uint32_t *time_ms, RawData *raw) {
    uint8_t expected;

    if (p->bytes[0] != 0xAA || p->bytes[1] != 0x55) {
        return false;
    }

    expected = calc_checksum(p->bytes, PACKET_SIZE - 1);
    if (expected != p->bytes[PACKET_SIZE - 1]) {
        return false;
    }

    *seq = read_u16(p->bytes, 2);
    *time_ms = read_u32(p->bytes, 4);

    raw->ax = (int16_t)read_u16(p->bytes, 8);
    raw->ay = (int16_t)read_u16(p->bytes, 10);
    raw->az = (int16_t)read_u16(p->bytes, 12);
    raw->gx = (int16_t)read_u16(p->bytes, 14);
    raw->gy = (int16_t)read_u16(p->bytes, 16);
    raw->gz = (int16_t)read_u16(p->bytes, 18);

    return true;
}
