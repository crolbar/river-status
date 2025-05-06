.PHONY: all

CC=gcc

OUT=main

CFLAGS=`pkg-config --cflags --libs wayland-client`

SRC=main.c \
	river-status-unstable-v1.c \
	output_status.c \
	seat_status.c \
	output.c \
	printers.c


PRO=river-status-unstable-v1.xml

PRO_OUT=river-status-unstable-v1.c river-status-unstable-v1.h

$(OUT): $(SRC) $(PRO_OUT)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)


$(PRO_OUT): $(PRO)
	wayland-scanner client-header river-status-unstable-v1.xml river-status-unstable-v1.h
	wayland-scanner private-code river-status-unstable-v1.xml river-status-unstable-v1.c


run: clean $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
