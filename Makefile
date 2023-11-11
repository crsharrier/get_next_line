NAME:= get_next_line
CC:= cc
CFLAGS:= -Wall -Wextra -Werror
SRCS:= get_next_line.c testing.c get_next_line_utils.c
OBJS := $(SRCS:.c=.o)

#BUFFER:= -D BUFFER_SIZE=9223372036854775807
BUFFER:= -D BUFFER_SIZE=1

all:$(NAME)

test:$(NAME)
	make re && ./$(NAME) testfiles/helloworld.txt
#./$(NAME) testfiles/emptyfile.txt
#./$(NAME) testfiles/helloworld.txt

stdin:$(NAME)
	make re && ./$(NAME) 0

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(BUFFER) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
