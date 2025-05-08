#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-client.h>

#include "river-status-unstable-v1.h"

#include "main.h"
#include "output.h"
#include "output_status.h"
#include "seat_status.h"
#include "wayland-client-protocol.h"

static struct zriver_status_manager_v1* status_mgr = NULL;

static struct zriver_output_status_v1* out_status = NULL;
static bool out_status_listener_set = false;

static struct zriver_seat_status_v1* seat_status = NULL;
static bool seat_status_listener_set = false;

struct wl_display* wl_display = NULL;
struct wl_registry* wl_registry = NULL;
struct wl_output* wl_output = NULL;
struct wl_seat* wl_seat = NULL;

struct WLOutputData* wl_output_data = NULL;
struct OutputStatusData* output_status_data = NULL;
struct SeatStatusData* seat_status_data = NULL;

bool print_human = true;
bool print_json = false;

static void
parse_args(char** argv, int argc)
{
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--json") == 0) {
            print_json = true;
            print_human = false;
        }
    }
}

static void
init_globals()
{
    wl_output_data = calloc(1, sizeof(struct WLOutputData));
    output_status_data = calloc(1, sizeof(struct OutputStatusData));
    seat_status_data = calloc(1, sizeof(struct SeatStatusData));
}

static void
clean_globals()
{
    if (wl_output_data != NULL) {
        if (wl_output_data->name != NULL)
            free(wl_output_data->name);

        if (wl_output_data->description != NULL)
            free(wl_output_data->description);

        if (wl_output_data->make != NULL)
            free(wl_output_data->make);

        if (wl_output_data->model != NULL)
            free(wl_output_data->model);

        free(wl_output_data);
    }

    if (output_status_data != NULL) {
        if (output_status_data->layout_name != NULL)
            free(output_status_data->layout_name);

        if (output_status_data->view_tags != NULL) {
            wl_array_release(output_status_data->view_tags);
            free(output_status_data->view_tags);
        }

        free(output_status_data);
    }

    if (seat_status_data != NULL) {
        if (seat_status_data->focused_view != NULL)
            free(seat_status_data->focused_view);

        if (seat_status_data->keymap_mode_name != NULL)
            free(seat_status_data->keymap_mode_name);

        free(seat_status_data);
    }
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

    if (strcmp(interface, "wl_output") == 0) {
        wl_output =
          wl_registry_bind(wl_registry, name, &wl_output_interface, version);

        /* WL_OUTPUT LISTENER */
        wl_output_add_listener(wl_output, &output_listener, wl_output_data);
    }

    if (strcmp(interface, "wl_seat") == 0) {
        wl_seat =
          wl_registry_bind(wl_registry, name, &wl_seat_interface, version);
    }

    /* output listeners */
    if (wl_output && status_mgr && !out_status_listener_set) {
        out_status = zriver_status_manager_v1_get_river_output_status(
          status_mgr, wl_output);

        /* OUTPUT STATUS LISTENER */
        zriver_output_status_v1_add_listener(
          out_status, &output_status_listeners, output_status_data);

        out_status_listener_set = true;
    }

    /* seat listeners */
    if (wl_seat && status_mgr && !seat_status_listener_set) {
        seat_status =
          zriver_status_manager_v1_get_river_seat_status(status_mgr, wl_seat);

        /* SEAT STATUS LISTENER */
        zriver_seat_status_v1_add_listener(
          seat_status, &seat_listeners, seat_status_data);

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
    if (status_mgr != NULL)
        zriver_status_manager_v1_destroy(status_mgr);

    if (out_status != NULL)
        zriver_output_status_v1_destroy(out_status);

    if (seat_status != NULL)
        zriver_seat_status_v1_destroy(seat_status);

    if (wl_registry != NULL)
        wl_registry_destroy(wl_registry);

    if (wl_output != NULL)
        wl_output_destroy(wl_output);

    if (wl_seat != NULL)
        wl_seat_destroy(wl_seat);

    if (wl_display != NULL)
        wl_display_disconnect(wl_display);
}

int
main(int argc, char** argv)
{
    parse_args(argv, argc);
    init_globals();
    if (init_wayland()) {
        while (wl_display_dispatch(wl_display) != -1) {
        }
    }
    finish_wayland();
    clean_globals();
    return 0;
}
