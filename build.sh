#!/usr/bin/env bash

gcc \
    -o river_state \
    main.c \
    river-status-unstable-v1.c \
    wlr-foreign-toplevel-management-unstable-v1.c \
    `pkg-config --cflags --libs wayland-client`

if [ "$*" == "run" ]; then
    ./river_state
fi
