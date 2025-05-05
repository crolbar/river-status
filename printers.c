#include "main.h"
#include <stdio.h>
#include <wayland-client.h>

static void
print_human_wl_output_data()
{
    if (wl_output_data->name == NULL) {
        return;
    }
    if (wl_output_data->description == NULL) {
        return;
    }

    printf("Output: %s\n"
           "  name: %s\n"
           "  description: %s\n"
           "  make: %s\n"
           "  model: %s\n"
           "  transform: %d\n"
           "  flags: %d\n"
           "  physical_width: %d\n"
           "  physical_height: %d\n"
           "  subpixel: %d\n"
           "  x: %d\n"
           "  y: %d\n"
           "  width: %d\n"
           "  height: %d\n"
           "  refresh: %d\n"
           "  factor: %d\n",
           wl_output_data->name,
           wl_output_data->name,
           wl_output_data->description,
           wl_output_data->make,
           wl_output_data->model,
           wl_output_data->transform,
           wl_output_data->flags,
           wl_output_data->physical_width,
           wl_output_data->physical_height,
           wl_output_data->subpixel,
           wl_output_data->x,
           wl_output_data->y,
           wl_output_data->width,
           wl_output_data->height,
           wl_output_data->refresh,
           wl_output_data->factor);
}

void
print_wl_output_data()
{
    if (print_human) {
        print_human_wl_output_data();
        return;
    }
}

void
print_bitmask(uint32_t value)
{
    for (int i = 10; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
}

void
print_human_output_status_data()
{
    if (output_status_data->layout_name == NULL)
        return;

    printf("focused_tags: %d\n"
           "urgent_tags: %d\n"
           "layout_name: %s\n",
           output_status_data->focused_tags,
           output_status_data->urgent_tags,
           output_status_data->layout_name);

    uint32_t* vtags = output_status_data->view_tags->data;
    size_t n = output_status_data->view_tags->size / sizeof(uint32_t);
    printf("view_tags: [");
    for (size_t i = 0; i < n; i++) {
        print_bitmask(vtags[i]);
        if (i != n - 1)
            printf(", ");
    }
    printf("]\n");
}

void
print_output_status_data()
{
    if (print_human) {
        print_human_output_status_data();
        return;
    }
}

void
print_human_seat_status_data()
{
    if (seat_status_data->focused_view == NULL)
        return;

    if (seat_status_data->keymap_mode_name == NULL)
        return;

    printf("focused_view: %s\n"
           "keymap_mode_name: %s\n",
           seat_status_data->focused_view,
           seat_status_data->keymap_mode_name);
}

void
print_seat_status_data()
{
    if (print_human) {
        print_human_seat_status_data();
        return;
    }
}

void
print_human_foreign_toplevel_data()
{
    if (foreign_toplevel_data->title == NULL)
        return;

    if (foreign_toplevel_data->app_id == NULL)
        return;

    printf("title: %s\n"
           "app_id: %s\n",
           foreign_toplevel_data->title,
           foreign_toplevel_data->app_id);
}

void
print_foreign_toplevel_data()
{
    if (print_human) {
        print_human_foreign_toplevel_data();
        return;
    }
}
