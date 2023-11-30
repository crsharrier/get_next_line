NAME:= get_next_line
TEST_NAME:= test.out
CC:= cc
CFLAGS:= -Wall -Wextra -Werror
SRCS:= get_next_line.c get_next_line_utils.c
OBJS := $(SRCS:.c=.o)

#TESTFILE:= testfiles/emptyfile.txt
TESTFILE:= testfiles/helloworld.txt

#BUFFER:= -D BUFFER_SIZE=9223372036854775807
BUFFER:= -D BUFFER_SIZE=42

all:$(NAME)

test:
	$(CC) $(BUFFER) $(SRCS) testing.c -g -o $(TEST_NAME)

stdin:$(NAME)
	make re && ./$(TEST_NAME) 0

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(BUFFER) -c $< -o $@

clean:
	rm -f $(OBJS) testing.o

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all
