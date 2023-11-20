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
	printf("\n===== TEST SPLIT =====\n");
	char *split_str1 = "Hello\nWorld";
	char *split_str2 = "";
	char *split_str3 = "Hello\n";
	char *split_str4 = "\n";
	char *split_result = NULL;

	ft_split(split_str1, &split_result, false);
	printf("First half of %s = %s\n", split_str1, split_result);
	ft_split(split_str1, &split_result, true);
	printf("Second half of %s = %s\n", split_str1, split_result);
	ft_split(split_str2, &split_result, false);
	printf("First half of %s = %s\n", split_str2, split_result);
	ft_split(split_str2, &split_result, true);
	printf("Second half of %s = %s\n", split_str2, split_result);
	ft_split(split_str3, &split_result, false);
	printf("First half of %s = %s\n", split_str3, split_result);
	ft_split(split_str3, &split_result, true);
	printf("Second half of %s = %s\n", split_str3, split_result);
	ft_split(split_str4, &split_result, false);
	printf("First half of %s = %s\n", split_str4, split_result);
	ft_split(split_str4, &split_result, true);
	printf("Second half of %s = %s\n", split_str4, split_result);
/*
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
*/
}

//read from FILENAME line my line
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
		while(1)
		{
			//printf_visible_newlines(result);
			printf("%s", result);
			result = get_next_line(fd);
			if (!result)
			{
				printf("%s", result);
				break ;
			}
		}
	}
	else
		printf("Either READ ERROR or File \"%s\" is empty!\n", filename);
	printf("============================================================\n");
}

int main(void)
{
	char	*testfile = "testfiles/helloworld";
	char	*status;
	int		fd;
	int		c;

	fd = open(testfile, O_RDONLY);

	//printf("result = %s\n", get_next_line(fd));

	printf("Testfile = %s\n", testfile);
	test_filename(testfile);

	//test_helpers();

	close(fd);
	return (0);
}