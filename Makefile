NAME:= get_next_line
CC:= cc
CFLAGS:= -Wall -Wextra -Werror
SRCS:= get_next_line main get_next_line_utils
PREPROC:= -D BUFFER_SIZE=4

all:
	$(CC) $(CFLAGS) $(PREPROC) get_next_line.c main.c get_next_line_utils.c

test:
	$(CC) $(PREPROC) get_next_line.c main.c get_next_line_utils.c
