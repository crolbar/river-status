#include <stdint.h>
#include <stdio.h>
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
    printf("Output geometry: %s %s at (%d, %d), p: %p\n",
           make,
           model,
           x,
           y,
           wl_output);
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
    printf("Output mode: %dx%d @ %d Hz\n", width, height, refresh / 1000);
}

/* OUTPUT NAME */
void
handle_output_name(void* data, struct wl_output* wl_output, const char* name)
{
    printf("Output name: %s\n", name);
}

/* OUTPUT SCALE */
void
handle_output_scale(void* data, struct wl_output* wl_output, int32_t factor)
{
    printf("Output scale: %d\n", factor);
}

/* OUTPUT DESCRIPTION */
void
handle_output_description(void* data,
                          struct wl_output* wl_output,
                          const char* description)
{
    printf("Output description: %s\n", description);
}

void
handle_output_done(void* data, struct wl_output* wl_output)
{
}
