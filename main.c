#include "river-status-unstable-v1.h"
#include "wlr-foreign-toplevel-management-unstable-v1.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-client.h>

static struct zriver_status_manager_v1* status_mgr = NULL;

static struct zriver_output_status_v1* out_status = NULL;
static bool out_status_listener_set = false;

static struct zriver_seat_status_v1* seat_status = NULL;
static bool seat_status_listener_set = false;

static struct zwlr_foreign_toplevel_manager_v1* toplevel_mgr = NULL;
static bool toplevel_mgr_listener_set = false;

struct wl_display* wl_display;
struct wl_registry* wl_registry;
struct wl_output* wl_output = NULL;
struct wl_seat* wl_seat = NULL;

static void
handle_focused_tags(void* data,
                    struct zriver_output_status_v1* zriver_output_status_v1,
                    uint32_t tags)
{
    printf("Output %p focused_tags = 0x%08x\n", zriver_output_status_v1, tags);
}

static void
handle_view_tags(void* data,
                 struct zriver_output_status_v1* zriver_output_status_v1,
                 struct wl_array* tags)
{
    uint32_t* vtags = tags->data;
    size_t n = tags->size / sizeof(uint32_t);
    printf("Output %p view_tags:", zriver_output_status_v1);
    for (size_t i = 0; i < n; i++) {
        printf(" [0x%08x]", vtags[i]);
    }
    printf("\n");
}

static void
handle_urgent_tags(void* data,
                   struct zriver_output_status_v1* zriver_output_status_v1,
                   uint32_t tags)
{
    printf("Output %p urgent_tags = 0x%08x\n", zriver_output_status_v1, tags);
}

static void
handle_layout_name(void* data,
                   struct zriver_output_status_v1* zriver_output_status_v1,
                   const char* name)
{
    printf("Output %p layout_name = %s\n", zriver_output_status_v1, name);
}

static void
handle_layout_name_clear(
  void* data,
  struct zriver_output_status_v1* zriver_output_status_v1)
{
}

static void
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

static void
handle_output_mode(void* data,
                   struct wl_output* wl_output,
                   uint32_t flags,
                   int32_t width,
                   int32_t height,
                   int32_t refresh)
{
    printf("Output mode: %dx%d @ %d Hz\n", width, height, refresh / 1000);
}

static void
handle_output_name(void* data, struct wl_output* wl_output, const char* name)
{
    printf("Output name: %s\n", name);
}

static void
handle_output_scale(void* data, struct wl_output* wl_output, int32_t factor)
{
    printf("Output scale: %d\n", factor);
}

static void
handle_output_description(void* data,
                          struct wl_output* wl_output,
                          const char* description)
{
    printf("Output description: %s\n", description);
}

static void
handle_output_done(void* data, struct wl_output* wl_output)
{
}

static const struct wl_output_listener output_listener = {
    .geometry = handle_output_geometry,
    .mode = handle_output_mode,
    .name = handle_output_name,
    .scale = handle_output_scale,
    .description = handle_output_description,
    .done = handle_output_done,
};

static void
handle_focused_output(void* data,
                      struct zriver_seat_status_v1* zriver_seat_status_v1,
                      struct wl_output* output)
{
    printf("Focused Output: %p\n", output);
}

static void
handle_unfocused_output(void* data,
                        struct zriver_seat_status_v1* zriver_seat_status_v1,
                        struct wl_output* output)
{
    printf("Unfocused Output: %p\n", output);
}

static void
handle_focused_view(void* data,
                    struct zriver_seat_status_v1* zriver_seat_status_v1,
                    const char* title)
{
    printf("Focused View: %s\n", title);
}

static void
handle_mode(void* data,
            struct zriver_seat_status_v1* zriver_seat_status_v1,
            const char* name)
{
    printf("Mode: %s\n", name);
}

static void
handle_toplevel_title(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  const char* title)
{
    printf("title: %s\n", title);
}

static void
handle_toplevel_app_id(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  const char* app_id)
{
    printf("app_id: %s\n", app_id);
}

static void
handle_toplevel_output_enter(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  struct wl_output* output)
{
    printf("output enter: %p\n", output);
}

static void
handle_toplevel_output_leave(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  struct wl_output* output)
{
    printf("output leave: %p\n", output);
}

static void
handle_toplevel_state(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  struct wl_array* state)
{
}

static void
handle_toplevel_done(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1)
{
    printf("done\n");
}

static void
handle_toplevel_closed(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1)
{
    printf("closed\n");
}

static void
handle_toplevel_parent(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  struct zwlr_foreign_toplevel_handle_v1* parent)
{
}

static struct zwlr_foreign_toplevel_handle_v1_listener
  toplevel_handle_listener = {
      .app_id = handle_toplevel_app_id,
      .title = handle_toplevel_title,
      .closed = handle_toplevel_closed,
      .done = handle_toplevel_done,
      .output_enter = handle_toplevel_output_enter,
      .output_leave = handle_toplevel_output_leave,
      .parent = handle_toplevel_parent,
      .state = handle_toplevel_state,
  };

static void
handle_toplevel(
  void* data,
  struct zwlr_foreign_toplevel_manager_v1* zwlr_foreign_toplevel_manager_v1,
  struct zwlr_foreign_toplevel_handle_v1* toplevel)
{
    zwlr_foreign_toplevel_handle_v1_add_listener(
      toplevel, &toplevel_handle_listener, NULL);
}

static void
handle_finished(
  void* data,
  struct zwlr_foreign_toplevel_manager_v1* zwlr_foreign_toplevel_manager_v1)
{
    printf("finished\n");
}

static void
registry_global(void* data,
                struct wl_registry* wl_registry,
                uint32_t name,
                const char* interface,
                uint32_t version)
{
    // printf("interface: %s\n", interface);

    if (strcmp(interface, "zriver_status_manager_v1") == 0) {
        status_mgr = wl_registry_bind(
          wl_registry, name, &zriver_status_manager_v1_interface, 4);
    }

    if (strcmp(interface, "zwlr_foreign_toplevel_manager_v1") == 0) {
        toplevel_mgr =
          wl_registry_bind(wl_registry,
                           name,
                           &zwlr_foreign_toplevel_manager_v1_interface,
                           version);
    }

    if (strcmp(interface, "wl_output") == 0) {
        wl_output =
          wl_registry_bind(wl_registry, name, &wl_output_interface, version);

        wl_output_add_listener(wl_output, &output_listener, data);
    }

    if (strcmp(interface, "wl_seat") == 0) {
        wl_seat =
          wl_registry_bind(wl_registry, name, &wl_seat_interface, version);
    }

    if (toplevel_mgr && !toplevel_mgr_listener_set) {
        static const struct zwlr_foreign_toplevel_manager_v1_listener
          listener = {
              .toplevel = handle_toplevel,
              .finished = handle_finished,
          };

        zwlr_foreign_toplevel_manager_v1_add_listener(
          toplevel_mgr, &listener, NULL);

        toplevel_mgr_listener_set = true;
    }

    /* output listeners */
    if (wl_output && status_mgr && !out_status_listener_set) {
        out_status = zriver_status_manager_v1_get_river_output_status(
          status_mgr, wl_output);

        static const struct zriver_output_status_v1_listener out_listeners = {
            .focused_tags = handle_focused_tags,
            .view_tags = handle_view_tags,
            .urgent_tags = handle_urgent_tags,
            .layout_name = handle_layout_name,
            .layout_name_clear = handle_layout_name_clear,
        };

        zriver_output_status_v1_add_listener(out_status, &out_listeners, NULL);

        out_status_listener_set = true;
    }

    /* seat listeners */
    if (wl_seat && status_mgr && !seat_status_listener_set) {
        seat_status =
          zriver_status_manager_v1_get_river_seat_status(status_mgr, wl_seat);

        static const struct zriver_seat_status_v1_listener seat_listeners = {
            .mode = handle_mode,
            .focused_output = handle_focused_output,
            .unfocused_output = handle_unfocused_output,
            .focused_view = handle_focused_view,
        };

        zriver_seat_status_v1_add_listener(seat_status, &seat_listeners, NULL);

        seat_status_listener_set = true;
    }
}

static void
registry_global_remove(void* data, struct wl_registry* registry, uint32_t name)
{
}

static const struct wl_registry_listener registry_listener = {
    .global = registry_global,
    .global_remove = registry_global_remove,
};

static bool
init_wayland(void)
{
    const char* display_name = getenv("WAYLAND_DISPLAY");
    if (display_name == NULL) {
        fputs("WAYLAND_DISPLAY is not set.\n", stderr);
        return false;
    }

    wl_display = wl_display_connect(display_name);
    if (wl_display == NULL) {
        fputs("Can not connect to Wayland server.\n", stderr);
        return false;
    }

    wl_registry = wl_display_get_registry(wl_display);
    wl_registry_add_listener(wl_registry, &registry_listener, NULL);

    wl_display_roundtrip(wl_display);

    return true;
}

static void
finish_wayland(void)
{
    if (wl_display == NULL)
        return;

    if (status_mgr != NULL)
        zriver_status_manager_v1_destroy(status_mgr);

    if (out_status != NULL)
        zriver_output_status_v1_destroy(out_status);

    if (seat_status != NULL)
        zriver_seat_status_v1_destroy(seat_status);

    if (toplevel_mgr != NULL)
        zwlr_foreign_toplevel_manager_v1_destroy(toplevel_mgr);

    wl_registry_destroy(wl_registry);
    wl_display_disconnect(wl_display);
}

int
main(int argc, char* argv[])
{
    if (init_wayland()) {
        while (wl_display_dispatch(wl_display) != -1) {
        }
    }
    finish_wayland();
    return 0;
}
