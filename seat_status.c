#include "main.h"
#include "river-status-unstable-v1.h"
#include <stdlib.h>
#include <string.h>

/* FOCUSED OUTPUT */
void
handle_focused_output(void* data,
                      struct zriver_seat_status_v1* zriver_seat_status_v1,
                      struct wl_output* output)
{
    SeatStatusData* seat_status_data = data;
    seat_status_data->focused_output = wl_output_data;
}

/* UNFOCUSED OUTPUT */
void
handle_unfocused_output(void* data,
                        struct zriver_seat_status_v1* zriver_seat_status_v1,
                        struct wl_output* output)
{
    SeatStatusData* seat_status_data = data;
    seat_status_data->unfocused_output = wl_output_data;
}

/* FOCUSED VIEW TITLE */
void
handle_focused_view(void* data,
                    struct zriver_seat_status_v1* zriver_seat_status_v1,
                    const char* title)
{
    SeatStatusData* seat_status_data = data;
    if (seat_status_data->focused_view != NULL)
        free(seat_status_data->focused_view);

    seat_status_data->focused_view = strdup(title);

    print_data();
}

/* KEYMAP MODE */
void
handle_mode(void* data,
            struct zriver_seat_status_v1* zriver_seat_status_v1,
            const char* name)
{
    SeatStatusData* seat_status_data = data;
    if (seat_status_data->keymap_mode_name != NULL)
        free(seat_status_data->keymap_mode_name);

    seat_status_data->keymap_mode_name = strdup(name);

    print_data();
}
