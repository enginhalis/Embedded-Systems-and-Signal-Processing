#include "imu_utils.h"

#include <stdlib.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

double now_us(void) {
#ifdef _WIN32
    static LARGE_INTEGER freq;
    static int freq_ready = 0;
    LARGE_INTEGER counter;

    if (!freq_ready) {
        QueryPerformanceFrequency(&freq);
        freq_ready = 1;
    }

    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart * 1000000.0 / (double)freq.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1000000.0 + (double)ts.tv_nsec / 1000.0;
#endif
}

double elapsed_us(double start_us, double end_us) {
    double dt = end_us - start_us;

    if (dt < 0.0) {
        dt = 0.0;
    }

    if (dt > 0.0 && dt < 0.001) {
        dt = 0.001;
    }

    return dt;
}

double rand_uniform(void) {
    return (double)rand() / (double)RAND_MAX;
}

double rand_gauss(double sigma) {
    double u1 = rand_uniform();
    double u2 = rand_uniform();

    if (u1 < 1e-12) {
        u1 = 1e-12;
    }

    return sigma * sqrt(-2.0 * log(u1)) * cos(2.0 * PI * u2);
}

int16_t clamp_i16(double x) {
    if (x > 32767.0) return 32767;
    if (x < -32768.0) return -32768;
    return (int16_t)lround(x);
}

const char *scenario_name(Scenario s) {
    switch (s) {
        case SC_NORMAL:         return "NORMAL";
        case SC_PACKET_LOSS:    return "PACKET_LOSS";
        case SC_CORRUPT_PACKET: return "CORRUPT_PACKET";
        case SC_DELAYED_PACKET: return "DELAYED_PACKET";
        default:                return "UNKNOWN";
    }
}

const char *status_name(Status s) {
    switch (s) {
        case ST_OK:       return "OK";
        case ST_EMPTY:    return "EMPTY";
        case ST_CHECKSUM: return "CHECKSUM";
        case ST_OVERFLOW: return "OVERFLOW";
        default:          return "UNKNOWN";
    }
}

void queue_init(PacketQueue *q) {
    q->count = 0;
}

bool queue_push(PacketQueue *q, const Packet *p) {
    if (q->count >= QUEUE_SIZE) {
        return false;
    }

    q->items[q->count++] = *p;
    return true;
}

bool queue_pop(PacketQueue *q, Packet *p) {
    int i;

    if (q->count == 0) {
        return false;
    }

    *p = q->items[0];

    for (i = 1; i < q->count; i++) {
        q->items[i - 1] = q->items[i];
    }

    q->count--;
    return true;
}
