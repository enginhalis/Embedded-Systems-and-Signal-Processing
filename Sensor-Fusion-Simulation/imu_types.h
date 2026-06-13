#ifndef IMU_TYPES_H
#define IMU_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define PI                 3.14159265358979323846
#define GRAVITY            9.80665

#define DT_SEC             0.01
#define SAMPLE_MS          10
#define PRINT_MS           100
#define SIM_DURATION_MS    5000

#define ACC_LSB_PER_G      16384.0
#define GYRO_LSB_PER_DPS   131.0

#define MA_WINDOW          5
#define LPF_ALPHA          0.35
#define COMP_ALPHA         0.98

#define ACC_NOISE_SIGMA    0.20
#define GYRO_NOISE_SIGMA   0.10

#define GYRO_BIAS_X_DPS     0.20
#define GYRO_BIAS_Y_DPS    -0.15
#define GYRO_BIAS_Z_DPS     0.10

#define GYRO_DRIFT_X_DPSPS  0.020
#define GYRO_DRIFT_Y_DPSPS -0.015
#define GYRO_DRIFT_Z_DPSPS  0.010

#define MOTION_HZ          0.5
#define ROLL_AMP_DEG       20.0
#define PITCH_AMP_DEG      15.0
#define YAW_AMP_DEG        8.0

#define PACKET_SIZE        24
#define QUEUE_SIZE         16

#define DEG2RAD(x) ((x) * PI / 180.0)
#define RAD2DEG(x) ((x) * 180.0 / PI)

typedef enum {
    SC_NORMAL = 0,
    SC_PACKET_LOSS,
    SC_CORRUPT_PACKET,
    SC_DELAYED_PACKET
} Scenario;

typedef enum {
    ST_OK = 0,
    ST_EMPTY,
    ST_CHECKSUM,
    ST_OVERFLOW
} Status;

typedef struct {
    double roll;
    double pitch;
    double yaw;
} Pose;

typedef struct {
    double roll;
    double pitch;
} Angle2D;

typedef struct {
    double ax, ay, az;
    double gx, gy, gz;
} ImuData;

typedef struct {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
} RawData;

typedef struct {
    uint8_t bytes[PACKET_SIZE];
} Packet;

typedef struct {
    Packet items[QUEUE_SIZE];
    int count;
} PacketQueue;

typedef struct {
    Packet packet;
    uint32_t release_ms;
    bool active;
} DelaySlot;

typedef struct {
    double buf[MA_WINDOW];
    double sum;
    int index;
    int count;
} AvgFilter;

typedef struct {
    double prev;
    bool ready;
} LowPassFilter;

typedef struct {
    AvgFilter ax, ay, az;
    LowPassFilter gx, gy, gz;

    double gyro_roll;
    double gyro_pitch;
    double gyro_yaw;
    bool gyro_ready;

    double comp_roll;
    double comp_pitch;
    bool comp_ready;
} FilterSet;

typedef struct {
    uint16_t seq;
    uint32_t time_ms;
    Status status;

    RawData raw;
    ImuData physical;
    ImuData filtered;

    Pose ideal;
    Angle2D acc_angle;
    Pose gyro_int_angle;
    Angle2D comp_angle;

    double proc_us;
} SampleView;

typedef struct {
    size_t generated;
    size_t injected;
    size_t processed;
    size_t lost;
    size_t corrupted;
    size_t delayed;
    size_t checksum_errors;
    size_t overflows;

    double total_proc_us;
    double max_proc_us;

    double roll_sq_err;
    double pitch_sq_err;
    size_t valid_angle_count;
} Stats;

#endif
