#include "main.h"
#include "string.h"
#include <stdint.h>
#include <wayland-client.h>

/* OUTPUT GEOMETRY */
void
handle_output_geometry(void* data,
                       struct wl_output* wl_output,
                       int32_t x,
                       int32_t y,
                       int32_t physical_width,
                       int32_t physical_height,
                       int32_t subpixel,
                       const char* make,
                       const char* model,
                       int32_t transform)
{
    WLOutputData* wl_output_data = data;

    wl_output_data->x = x;
    wl_output_data->y = y;
    wl_output_data->physical_width = physical_width;
    wl_output_data->physical_height = physical_height;
    wl_output_data->subpixel = subpixel;
    wl_output_data->make = strdup(make);
    wl_output_data->model = strdup(model);
    wl_output_data->transform = transform;

    print_wl_output_data();
}

/* OUTPUT MODE */
void
handle_output_mode(void* data,
                   struct wl_output* wl_output,
                   uint32_t flags,
                   int32_t width,
                   int32_t height,
                   int32_t refresh)
{
    WLOutputData* wl_output_data = data;

    wl_output_data->flags = flags;
    wl_output_data->width = width;
    wl_output_data->height = height;
    wl_output_data->refresh = refresh;

    print_wl_output_data();
}

/* OUTPUT NAME */
void
handle_output_name(void* data, struct wl_output* wl_output, const char* name)
{
    WLOutputData* wl_output_data = data;
    wl_output_data->name = strdup(name);

    print_wl_output_data();
}

/* OUTPUT SCALE */
void
handle_output_scale(void* data, struct wl_output* wl_output, int32_t factor)
{
    WLOutputData* wl_output_data = data;
    wl_output_data->factor = factor;

    print_wl_output_data();
}

/* OUTPUT DESCRIPTION */
void
handle_output_description(void* data,
                          struct wl_output* wl_output,
                          const char* description)
{
    WLOutputData* wl_output_data = data;
    wl_output_data->description = strdup(description);

    print_wl_output_data();
}

void
handle_output_done(void* data, struct wl_output* wl_output)
{
}
