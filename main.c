#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	int fd1;
	int fd2;

	fd1 = open("emptyfile.txt", O_RDONLY);
	fd2 = open("testfile.txt", O_RDONLY);

	printf("Result for emptyfile.txt = %s\n", get_next_line(fd1));
	printf("Result for testfile.txt = %s\n", get_next_line(fd2));
	printf("Result for testfile.txt = %s\n", get_next_line(fd2));
	printf("Result for testfile.txt = %s\n", get_next_line(fd2));
	printf("Result for fd1 = %s\n", get_next_line(1));
	return (0);
}