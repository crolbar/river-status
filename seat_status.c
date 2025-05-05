#include "river-status-unstable-v1.h"
#include <stdio.h>

/* FOCUSED OUTPUT */
void
handle_focused_output(void* data,
                      struct zriver_seat_status_v1* zriver_seat_status_v1,
                      struct wl_output* output)
{
    printf("Focused Output: %p\n", output);
}

/* UNFOCUSED OUTPUT */
void
handle_unfocused_output(void* data,
                        struct zriver_seat_status_v1* zriver_seat_status_v1,
                        struct wl_output* output)
{
    printf("Unfocused Output: %p\n", output);
}

/* FOCUSED VIEW TITLE */
void
handle_focused_view(void* data,
                    struct zriver_seat_status_v1* zriver_seat_status_v1,
                    const char* title)
{
    printf("Focused View: %s\n", title);
}

/* KEYMAP MODE */
void
handle_mode(void* data,
            struct zriver_seat_status_v1* zriver_seat_status_v1,
            const char* name)
{
    printf("Mode: %s\n", name);
}
