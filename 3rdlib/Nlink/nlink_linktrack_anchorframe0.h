#ifndef NLINK_LINKTRACK_ANCHORFRAME0_H
#define NLINK_LINKTRACK_ANCHORFRAME0_H




#include "nlink_utils.h"
#include "nlink_typedef.h"
#include "qdebug.h"
#pragma pack(1)
typedef struct {
  uint8_t id;
  linktrack_role_e role;
  float pos_3d[3];
  float dis_arr[8];
} nlt_anchorframe0_node_t;


typedef struct {
  linktrack_role_e role;
  uint8_t id;
  uint32_t local_time;
  uint32_t system_time;
  float voltage;
  uint8_t valid_node_count;
  nlt_anchorframe0_node_t *nodes[30];
} nlt_anchorframe0_result_t;


typedef struct {
    size_t fixed_part_size;
    uint8_t frame_header;
    uint8_t function_mark;
    uint8_t tail_check;
  nlt_anchorframe0_result_t result;
} nlt_anchorframe0_t;
#pragma pack(pop)

#pragma pack(1)
typedef struct {
    uint8_t id;
    uint8_t role;
    nint24_t pos_3d[3];
    uint16_t dis_arr[8];
} nlt_anchorframe0_tag_raw_t;

typedef struct {
    uint8_t header[2];
    nlt_anchorframe0_tag_raw_t nodes[30];
    uint8_t reserved0[67];
    uint32_t local_time;
    uint8_t reserved1[4];
    uint16_t voltage;
    uint32_t system_time;
    uint8_t id;
    uint8_t role;
    uint8_t tail_check;
} nlt_anchorframe0_raw_t;
#pragma pack()



inline bool UnpackData_nlt_anchorframe0(const uint8_t *data, size_t data_length,nlt_anchorframe0_t* results)
{
    static nlt_anchorframe0_raw_t g_frame;
    results->fixed_part_size = 896;
    results->frame_header = 0x55;
    results->function_mark = 0x00;
    results->tail_check = 0xee;

    if (data_length < results->fixed_part_size ||
        data[0] != results->frame_header ||
        data[1] != results->function_mark ||
        data[results->fixed_part_size - 1] !=
            results->tail_check)
    {
        return 0;
    }
    static uint8_t init_needed = 1;
    if (init_needed) {
        memset(results->result.nodes, 0,
               sizeof(results->result.nodes));
        init_needed = 0;
    }

    memcpy(&g_frame, data, results->fixed_part_size);
    results->result.role =static_cast<linktrack_role_e>(g_frame.role);
    results->result.id = g_frame.id;
    results->result.local_time = g_frame.local_time;
    results->result.system_time = g_frame.system_time;
    results->result.voltage = g_frame.voltage / MULTIPLY_VOLTAGE;
    results->result.valid_node_count = 0;


    for (size_t i = 0, count = ARRAY_LENGTH(results->result.nodes);i < count; ++i)
    {
        if (g_frame.nodes[i].id == 0xff)
        {
            continue;
        }

        uint8_t index = results->result.valid_node_count;
        TRY_MALLOC_NEW_NODE(results->result.nodes[index],
                            nlt_anchorframe0_node_t)

        results->result.nodes[index]->role =
            (linktrack_role_e)g_frame.nodes[i].role;
        results->result.nodes[index]->id = g_frame.nodes[i].id;
        NLINK_TRANSFORM_ARRAY_INT24(results->result.nodes[index]->pos_3d,
                                    g_frame.nodes[i].pos_3d, MULTIPLY_POS)
        NLINK_TRANSFORM_ARRAY(results->result.nodes[index]->dis_arr,
                              g_frame.nodes[i].dis_arr, 100.0f)

        ++results->result.valid_node_count;
    }
    return 1;
}


#endif // NLINK_LINKTRACK_ANCHORFRAME0_H
