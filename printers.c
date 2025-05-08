#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-client.h>

char*
json_encode_string(const char* input)
{
    size_t len = strlen(input);
    size_t max_output_len = len * 6 + 3;
    char* output = malloc(max_output_len);
    if (!output)
        return NULL;

    char* out = output;
    *out++ = '"';

    for (size_t i = 0; i < len; ++i) {
        unsigned char c = input[i];
        switch (c) {
            case '\"':
                *out++ = '\\';
                *out++ = '\"';
                break;
            case '\\':
                *out++ = '\\';
                *out++ = '\\';
                break;
            case '\b':
                *out++ = '\\';
                *out++ = 'b';
                break;
            case '\f':
                *out++ = '\\';
                *out++ = 'f';
                break;
            case '\n':
                *out++ = '\\';
                *out++ = 'n';
                break;
            case '\r':
                *out++ = '\\';
                *out++ = 'r';
                break;
            case '\t':
                *out++ = '\\';
                *out++ = 't';
                break;
            default:
                if (c < 0x20) {
                    out += sprintf(out, "\\u%04x", c);
                } else {
                    *out++ = c;
                }
                break;
        }
    }

    *out++ = '"';
    *out = '\0';
    return output;
}

int
get_int_length(int num)
{
    if (num == 0)
        return 1;

    int len = 0;

    if (num < 0) {
        len++;
        num = -num;
    }

    while (num > 0) {
        num /= 10;
        len++;
    }

    return len;
}

char*
int_to_string(int num)
{
    int temp = num, length = 0;

    if (num == 0)
        length = 1;
    else {
        while (temp > 0) {
            temp /= 10;
            length++;
        }
    }

    char* str = malloc(length + 1);
    str[length] = '\0';

    if (num == 0) {
        str[0] = '0';
        return str;
    }

    while (num > 0) {
        str[--length] = (num % 10) + '0';
        num /= 10;
    }

    return str;
}

static char*
get_human_wl_output_data()
{
    if (wl_output_data->name == NULL) {
        return "";
    }
    if (wl_output_data->description == NULL) {
        return "";
    }

    // printf("Output: %s\n"
    //        "  name: %s\n"
    //        "  description: %s\n"
    //        "  make: %s\n"
    //        "  model: %s\n"
    //        "  transform: %d\n"
    //        "  flags: %d\n"
    //        "  physical_width: %d\n"
    //        "  physical_height: %d\n"
    //        "  subpixel: %d\n"
    //        "  x: %d\n"
    //        "  y: %d\n"
    //        "  width: %d\n"
    //        "  height: %d\n"
    //        "  refresh: %d\n"
    //        "  factor: %d\n",
    //        wl_output_data->name,
    //        wl_output_data->name,
    //        wl_output_data->description,
    //        wl_output_data->make,
    //        wl_output_data->model,
    //        wl_output_data->transform,
    //        wl_output_data->flags,
    //        wl_output_data->physical_width,
    //        wl_output_data->physical_height,
    //        wl_output_data->subpixel,
    //        wl_output_data->x,
    //        wl_output_data->y,
    //        wl_output_data->width,
    //        wl_output_data->height,
    //        wl_output_data->refresh,
    //        wl_output_data->factor);

    return "wl_output human";
}

static char*
get_json_wl_output_data()
{
    return "wl_output json";
}

// TODO!!
static void
print_bitmask(uint32_t value)
{
    for (int i = 10; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
}

static char*
get_human_output_status_data()
{
    if (output_status_data->layout_name == NULL)
        return "";

    // printf("focused_tags: %d\n"
    //        "urgent_tags: %d\n"
    //        "layout_name: %s\n",
    //        output_status_data->focused_tags,
    //        output_status_data->urgent_tags,
    //        output_status_data->layout_name);

    // uint32_t* vtags = output_status_data->view_tags->data;
    // size_t n = output_status_data->view_tags->size / sizeof(uint32_t);
    // printf("view_tags: [");
    // for (size_t i = 0; i < n; i++) {
    //     print_bitmask(vtags[i]);
    //     if (i != n - 1)
    //         printf(", ");
    // }
    // printf("]\n");

    return "output status human";
}

int
get_single_tag_human(uint32_t tags)
{
    for (int i = 0; i < 32; i++) {
        if ((tags >> i & 1) == 1) {
            return i + 1;
        }
    }
    return 0;
}

static char*
get_json_output_status_data()
{
    if (output_status_data->layout_name == NULL)
        return "{}";

    int focused_tags = output_status_data->focused_tags;
    int urgent_tags = output_status_data->urgent_tags;
    char* layout_name = json_encode_string(output_status_data->layout_name);

    uint32_t* vtags = output_status_data->view_tags->data;
    size_t vt_size = output_status_data->view_tags->size / sizeof(uint32_t);
    char* view_tags = malloc((vt_size * 2) + 2);

    int vti = 0;
    view_tags[vti++] = '[';
    for (int i = 0; i < vt_size; i++) {
        int tag = get_single_tag_human(vtags[i]);
        char* tag_str = int_to_string(tag);
        for (int j = 0; j < strlen(tag_str); j++) {
            view_tags[vti++] = tag_str[j];
        }
        free(tag_str);

        if (i != vt_size - 1)
            view_tags[vti++] = ',';
    }
    view_tags[vti++] = ']';
    view_tags[vti] = '\0';

    char* fmt = "{\"focused_tags\": %d, \"urgent_tags\": %d, \"layout_name\": "
                "%s, \"view_tags\": %s}";

    size_t size = strlen(fmt) + strlen(layout_name) +
                  get_int_length(focused_tags) + get_int_length(urgent_tags) +
                  strlen(view_tags);

    char* out = malloc(size);

    sprintf(out, fmt, focused_tags, urgent_tags, layout_name, view_tags);

    free(layout_name);
    free(view_tags);

    return out;
}

static char*
get_human_seat_status_data()
{
    if (seat_status_data->focused_view == NULL)
        return "";

    if (seat_status_data->keymap_mode_name == NULL)
        return "";

    // printf("focused_view: %s\n"
    //        "keymap_mode_name: %s\n",
    //        seat_status_data->focused_view,
    //        seat_status_data->keymap_mode_name);
    return "seat status human";
}

static char*
get_json_seat_status_data()
{
    if (seat_status_data->focused_view == NULL)
        return "{}";

    if (seat_status_data->keymap_mode_name == NULL)
        return "{}";

    char* focused_view = json_encode_string(seat_status_data->focused_view);
    char* keymap_mode_name =
      json_encode_string(seat_status_data->keymap_mode_name);

    char* fmt = "{\"focused_view\": %s,\"keymap_mode_name\": %s}";
    size_t size = strlen(fmt) + strlen(focused_view) + strlen(keymap_mode_name);
    char* out = malloc(size);

    sprintf(out, fmt, focused_view, keymap_mode_name);

    free(focused_view);
    free(keymap_mode_name);

    return out;
}

static void
print_human_data()
{
    printf("human data\n");
}

static void
print_json_data()
{
    char* wl_output = get_json_wl_output_data();
    char* output_status = get_json_output_status_data();
    size_t output_status_len = strlen(output_status);
    char* seat_status = get_json_seat_status_data();
    size_t seat_status_len = strlen(seat_status);

    char* fmt = "{\"wl_output\": \"%s\", \"output_status\": %s, "
                "\"seat_status\": %s}\n";

    size_t size =
      strlen(wl_output) + output_status_len + seat_status_len + strlen(fmt);

    printf(fmt, wl_output, output_status, seat_status);

    if (output_status_len > 2)
        free(output_status);
    if (seat_status_len > 2)
        free(seat_status);
}

void
print_data()
{
    if (print_human) {
        print_human_data();
        return;
    }

    print_json_data();
    fflush(stdout);
}
