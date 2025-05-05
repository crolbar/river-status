#ifndef FOREIGN_TOPLEVEL
#define FOREIGN_TOPLEVEL

#include "wlr-foreign-toplevel-management-unstable-v1.h"

void
handle_toplevel_title(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  const char* title);

void
handle_toplevel_app_id(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  const char* app_id);

void
handle_toplevel_output_enter(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  struct wl_output* output);

void
handle_toplevel_output_leave(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  struct wl_output* output);

void
handle_toplevel_state(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  struct wl_array* state);

void
handle_toplevel_done(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1);

void
handle_toplevel_closed(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1);

void
handle_toplevel_parent(
  void* data,
  struct zwlr_foreign_toplevel_handle_v1* zwlr_foreign_toplevel_handle_v1,
  struct zwlr_foreign_toplevel_handle_v1* parent);

void
handle_toplevel(
  void* data,
  struct zwlr_foreign_toplevel_manager_v1* zwlr_foreign_toplevel_manager_v1,
  struct zwlr_foreign_toplevel_handle_v1* toplevel);

void
handle_finished(
  void* data,
  struct zwlr_foreign_toplevel_manager_v1* zwlr_foreign_toplevel_manager_v1);

const struct zwlr_foreign_toplevel_manager_v1_listener
  foreign_toplevel_listener = {
      .toplevel = handle_toplevel,
      .finished = handle_finished,
  };

#endif
