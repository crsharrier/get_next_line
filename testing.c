#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include <string.h>

void	printf_visible_newlines(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			printf("\\n\n");
		else
			printf("%c", *str);
		str++;
	}
}

void	test_helpers()
{
	printf("\n===== TEST STRAPPEND =====\n");
	char	*suffix = "World";
	char	*str = malloc(sizeof(char) * 6);
	strcpy(str, "Hello");
	printf("str before = %s\n", str);
	ft_strappend(suffix, &str);
	printf("str after = %s\n", str);
	printf("\n");

	free(str);
	str = malloc(sizeof(char));
	str[0] = '\0';
	printf("str before = %s\n", str);
	ft_strappend(suffix, &str);
	printf("str after = %s\n", str);

	printf("\n===== TEST STRCHR =====\n");
	printf("str = %s\n", str);
	printf("strchr(str, 'r') = %s\n", strchr(str, 'r'));
	printf("strchr(str, '\\n') = %s\n", strchr(str, '\n'));

	printf("\n===== TEST SUBSTRP =====\n");
	//char	*delim = ft_strchr(str, 'l');
	//printf("str = %s\n", str);
	//printf("substrp(%s, %s) = %s\n", str, delim, ft_substrp(&str, delim));
	//printf("\n");

	printf("\n===== TEST PSUBSTR =====\n");
	//printf("str = %s\n", str);
	//ft_psubstr(&str, delim);
	//printf("str after = %s\n", str);
	//printf("\n");

}

void	test_filename(char *filename)
{
	int		fd;
	char	*result;

	fd = open(filename, O_RDONLY);
	printf("\n==== buffer size = \033[0;32m%li\033[0m\n", (long)BUFFER_SIZE);
	printf("==== getting \033[0;32m%s\033[0m line by line:\n", filename);
	printf("============================================================\n");
	result = get_next_line(fd);
	if (result)
	{
		while(result)
		{
			printf_visible_newlines(result);
			//printf("%s", result);
			result = get_next_line(fd);
		}
	}
	else
		printf("Either READ ERROR or File \"%s\" is empty!\n", filename);
	printf("============================================================\n");
}

int main(int argc, char **argv)
{
	//test_helpers();
	if (argc != 2)
	{
		printf("Please provide a single testfile as argument, or '0' to read from stdin\n");
		return (0);	
	}
	if (strcmp(argv[1],"0") == 0)
		get_next_line(0);
	else 
	{
		//test_filename(argv[1]);
		int	fd = open(argv[1], O_RDONLY);
		get_next_line(fd);
		get_next_line(fd);
	}
	return (0);
}