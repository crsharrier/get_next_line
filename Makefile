NAME:= get_next_line
CC:= cc
CFLAGS:= -Wall -Wextra -Werror
SRCS:= get_next_line main get_next_line_utils

all:
	$(CC) $(CFLAGS) get_next_line.c main.c get_next_line_utils.c
