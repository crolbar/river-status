#include "main.h"
#include "river-status-unstable-v1.h"
#include <stdlib.h>
#include <string.h>

/* FOCUSED TAGS */
void
handle_focused_tags(void* data,
                    struct zriver_output_status_v1* zriver_output_status_v1,
                    uint32_t tags)
{
    OutputStatusData* output_status_data = data;
    output_status_data->focused_tags = tags;

    print_output_status_data();
}

/* VIEW TAGS (`tags` field of all views) */
void
handle_view_tags(void* data,
                 struct zriver_output_status_v1* zriver_output_status_v1,
                 struct wl_array* tags)
{
    OutputStatusData* output_status_data = data;

    if (output_status_data->view_tags != NULL)
        wl_array_release(output_status_data->view_tags);

    output_status_data->view_tags = malloc(sizeof(struct wl_array));
    wl_array_init(output_status_data->view_tags);
    wl_array_copy(output_status_data->view_tags, tags);

    print_output_status_data();
}

/* URGENT TAGS */
void
handle_urgent_tags(void* data,
                   struct zriver_output_status_v1* zriver_output_status_v1,
                   uint32_t tags)
{
    OutputStatusData* output_status_data = data;
    output_status_data->urgent_tags = tags;

    print_output_status_data();
}

/* LAYOUT NAME */
void
handle_layout_name(void* data,
                   struct zriver_output_status_v1* zriver_output_status_v1,
                   const char* name)
{
    OutputStatusData* output_status_data = data;
    output_status_data->layout_name = strdup(name);

    print_output_status_data();
}

void
handle_layout_name_clear(
  void* data,
  struct zriver_output_status_v1* zriver_output_status_v1)
{
}
