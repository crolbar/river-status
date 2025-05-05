#ifndef OUTPUT
#define OUTPUT

#include <stdint.h>
#include <stdio.h>
#include <wayland-client.h>

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
                       int32_t transform);

void
handle_output_mode(void* data,
                   struct wl_output* wl_output,
                   uint32_t flags,
                   int32_t width,
                   int32_t height,
                   int32_t refresh);

void
handle_output_name(void* data, struct wl_output* wl_output, const char* name);

void
handle_output_scale(void* data, struct wl_output* wl_output, int32_t factor);

void
handle_output_description(void* data,
                          struct wl_output* wl_output,
                          const char* description);

void
handle_output_done(void* data, struct wl_output* wl_output);

const struct wl_output_listener output_listener = {
    .geometry = handle_output_geometry,
    .mode = handle_output_mode,
    .done = handle_output_done,
    .scale = handle_output_scale,
    .name = handle_output_name,
    .description = handle_output_description,
};

#endif
