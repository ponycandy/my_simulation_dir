#ifndef NLINK_LINKTRACK_TAGFRAME0_H
#define NLINK_LINKTRACK_TAGFRAME0_H

#include "nlink_typedef.h"
#include "nlink_utils.h"

typedef struct {
  linktrack_role_e role;
  uint8_t id;
  float pos_3d[3];
  float eop_3d[3];
  float vel_3d[3];
  float dis_arr[8];
  float imu_gyro_3d[3];
  float imu_acc_3d[3];
  float angle_3d[3];
  float quaternion[4];
  uint32_t local_time;
  uint32_t system_time;
  float voltage;
} nlt_tagframe0_result_t;

typedef struct {
    size_t fixed_part_size;
    uint8_t frame_header;
    uint8_t function_mark;
  nlt_tagframe0_result_t result;
} nlt_tagframe0_t;


#pragma pack(1)

typedef struct {
    uint8_t header[2];
    uint8_t id;
    uint8_t role;
    nint24_t pos_3d[3];
    nint24_t vel_3d[3];
    nint24_t dis_arr[8];
    float imu_gyro_3d[3];
    float imu_acc_3d[3];
    uint8_t reserved1[12];
    int16_t angle_3d[3];
    float quaternion[4];
    uint8_t reserved2[4];
    uint32_t local_time;
    uint32_t system_time;
    uint8_t reserved3[1];
    uint8_t eop_3d[3];
    uint16_t voltage;
    uint8_t reserved4[5];
    uint8_t check_sum;
} nlt_tagframe0_raw_t;
#pragma pack()
// extern nlt_tagframe0_t g_nlt_tagframe0;
// static nlt_tagframe0_raw_t g_frame;

inline uint8_t UnpackData_nlt_tagframe0(const uint8_t *data, size_t data_length,nlt_tagframe0_t* results)
{
    nlt_tagframe0_raw_t g_frame;
    results->fixed_part_size = 128;
    results->frame_header = 0x55;
    results->function_mark = 0x01;

    if (data_length < results->fixed_part_size ||
        data[0] != results->frame_header ||
        data[1] != results->function_mark)
        return 0;
    if (!NLINK_VerifyCheckSum(data, results->fixed_part_size))
        return 0;

    memcpy(&g_frame, data, results->fixed_part_size);
    results->result.role = static_cast<linktrack_role_e>(g_frame.role);
    results->result.id = g_frame.id;
    results->result.local_time = g_frame.local_time;
    results->result.system_time = g_frame.system_time;
    results->result.voltage = g_frame.voltage / MULTIPLY_VOLTAGE;

    NLINK_TRANSFORM_ARRAY_INT24(results->result.pos_3d, g_frame.pos_3d,
                                MULTIPLY_POS)
    NLINK_TRANSFORM_ARRAY_INT24(results->result.vel_3d, g_frame.vel_3d,
                                MULTIPLY_VEL)
    NLINK_TRANSFORM_ARRAY_INT24(results->result.dis_arr, g_frame.dis_arr,
                                MULTIPLY_DIS)
    NLINK_TRANSFORM_ARRAY(results->result.imu_gyro_3d, g_frame.imu_gyro_3d,
                          1)
    NLINK_TRANSFORM_ARRAY(results->result.imu_acc_3d, g_frame.imu_acc_3d,
                          1)
    NLINK_TRANSFORM_ARRAY(results->result.quaternion, g_frame.quaternion,
                          1)
    NLINK_TRANSFORM_ARRAY(results->result.angle_3d, g_frame.angle_3d,
                          MULTIPLY_ANGLE)
    NLINK_TRANSFORM_ARRAY(results->result.eop_3d, g_frame.eop_3d,
                          MULTIPLY_EOP)

    return 1;
}




#endif // NLINK_LINKTRACK_TAGFRAME0_H
