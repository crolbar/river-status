#ifndef SEAT_STATUS
#define SEAT_STATUS
#include "river-status-unstable-v1.h"

void
handle_focused_output(void* data,
                      struct zriver_seat_status_v1* zriver_seat_status_v1,
                      struct wl_output* output);

void
handle_unfocused_output(void* data,
                        struct zriver_seat_status_v1* zriver_seat_status_v1,
                        struct wl_output* output);

void
handle_focused_view(void* data,
                    struct zriver_seat_status_v1* zriver_seat_status_v1,
                    const char* title);

void
handle_mode(void* data,
            struct zriver_seat_status_v1* zriver_seat_status_v1,
            const char* name);

const struct zriver_seat_status_v1_listener seat_listeners = {
    .focused_output = handle_focused_output,
    .unfocused_output = handle_unfocused_output,
    .focused_view = handle_focused_view,
    .mode = handle_mode,
};

#endif
