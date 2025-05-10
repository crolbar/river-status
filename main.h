#ifndef MAIN
#define MAIN

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern struct WLOutputData* wl_output_data;
extern struct OutputStatusData* output_status_data;
extern struct SeatStatusData* seat_status_data;

extern bool print_human;
extern bool print_json;

extern bool print_wl_output;
extern bool print_output_status;
extern bool print_seat_status;

typedef struct WLOutputData
{
    int32_t x;
    int32_t y;
    int32_t physical_width;
    int32_t physical_height;
    int32_t subpixel;
    char* make;
    char* model;
    int32_t transform;
    uint32_t flags;
    int32_t width;
    int32_t height;
    int32_t refresh;
    char* name;
    int32_t factor;
    char* description;
} WLOutputData;

typedef struct OutputStatusData
{
    uint32_t focused_tags;
    struct wl_array* view_tags;
    uint32_t urgent_tags;
    char* layout_name;
} OutputStatusData;

typedef struct SeatStatusData
{
    WLOutputData* focused_output;
    WLOutputData* unfocused_output;
    char* focused_view;
    char* keymap_mode_name;
} SeatStatusData;

void
print_data();

#endif
