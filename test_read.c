#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int		main(void)
{
	int fd1;
	int fd2;
	int result1;
	int result2;
	char *buf1[100];
	char *buf2[100];

	fd1 = open("testfile.txt", O_RDONLY);
	fd2 = open("emptyfile.txt", O_RDONLY);

	result1 = read(fd1, buf1, 6);
	result2 = read(fd2, buf2, 6);

	printf("read() return value for testfile = %i\n", result1);
	printf("read() return value for emptyfile = %i\n", result2);

	close(fd1);
	close(fd2);

}