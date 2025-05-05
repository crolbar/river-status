#include "wlr-foreign-toplevel-management-unstable-v1.h"
#include <stdio.h>

/* WINDOW TITLE */
void
handle_toplevel_title(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  const char* title)
{
    printf("title: %s\n", title);
}

/* WINDOW TITLE */
void
handle_toplevel_app_id(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  const char* app_id)
{
    printf("app_id: %s\n", app_id);
}

void
handle_toplevel_output_enter(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  struct wl_output* output)
{
}

void
handle_toplevel_output_leave(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  struct wl_output* output)
{
}

void
handle_toplevel_state(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  struct wl_array* state)
{
}

void
handle_toplevel_done(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1)
{
}

void
handle_toplevel_closed(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1)
{
}

void
handle_toplevel_parent(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  struct zwlr_foreign_toplevel_handle_v1* parent)
{
}

struct zwlr_foreign_toplevel_handle_v1_listener
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

void
handle_toplevel(
  void* data,
  struct zwlr_foreign_toplevel_manager_v1* zwlr_foreign_toplevel_manager_v1,
  struct zwlr_foreign_toplevel_handle_v1* toplevel)
{
    zwlr_foreign_toplevel_handle_v1_add_listener(
      toplevel, &toplevel_handle_listener, NULL);
}

void
handle_finished(
  void* data,
  struct zwlr_foreign_toplevel_manager_v1* zwlr_foreign_toplevel_manager_v1)
{
}
