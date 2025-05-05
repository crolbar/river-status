#ifndef OUTPUT_STATUS
#define OUTPUT_STATUS

#include "river-status-unstable-v1.h"
#include <stdint.h>

void
handle_focused_tags(void* data,
                    struct zriver_output_status_v1* zriver_output_status_v1,
                    uint32_t tags);

void
handle_view_tags(void* data,
                 struct zriver_output_status_v1* zriver_output_status_v1,
                 struct wl_array* tags);

void
handle_urgent_tags(void* data,
                   struct zriver_output_status_v1* zriver_output_status_v1,
                   uint32_t tags);

void
handle_layout_name(void* data,
                   struct zriver_output_status_v1* zriver_output_status_v1,
                   const char* name);

void
handle_layout_name_clear(
  void* data,
  struct zriver_output_status_v1* zriver_output_status_v1);

const struct zriver_output_status_v1_listener output_status_listeners = {
    .focused_tags = handle_focused_tags,
    .view_tags = handle_view_tags,
    .urgent_tags = handle_urgent_tags,
    .layout_name = handle_layout_name,
    .layout_name_clear = handle_layout_name_clear,
};

#endif
