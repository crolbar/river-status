#include <stdio.h>
#include "river-status-unstable-v1.h"

/* FOCUSED TAGS */
void
handle_focused_tags(void* data,
                    struct zriver_output_status_v1* zriver_output_status_v1,
                    uint32_t tags)
{
    printf("Output %p focused_tags = 0x%08x\n", zriver_output_status_v1, tags);
}

/* VIEW TAGS (`tags` field of all views) */
void
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

/* URGENT TAGS */
void
handle_urgent_tags(void* data,
                   struct zriver_output_status_v1* zriver_output_status_v1,
                   uint32_t tags)
{
    printf("Output %p urgent_tags = 0x%08x\n", zriver_output_status_v1, tags);
}

/* LAYOUT NAME */
void
handle_layout_name(void* data,
                   struct zriver_output_status_v1* zriver_output_status_v1,
                   const char* name)
{
    printf("Output %p layout_name = %s\n", zriver_output_status_v1, name);
}

void
handle_layout_name_clear(
  void* data,
  struct zriver_output_status_v1* zriver_output_status_v1)
{
}
