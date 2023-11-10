#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include <string.h>

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
	char	*delim = ft_strchr(str, 'l');
	printf("str = %s\n", str);
	printf("substrp(%s, %s) = %s\n", str, delim, ft_substrp(str, delim));
	printf("\n");

	printf("\n===== TEST PSUBSTR =====\n");
	printf("str = %s\n", str);
	ft_psubstr(&str, delim);
	printf("str after = %s\n", str);
	printf("\n");

}

int main(void)
{
	int		fd;
	char	*filename = "emptyfile.txt";
	char	*result;
	
	fd = open(filename, O_RDONLY);

	//test_helpers();
	

	printf("===========================\n");
	result = get_next_line(fd);
	if (result)
	{
		printf("CONTENTS OF \"%s\":\n", filename);
		while(result)
		{
			printf("%s\n", result);
			result = get_next_line(fd);
		}
	}
	else
		printf("ERROR File \"%s\" is empty!\n", filename);
	printf("===========================\n");

	//char *buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1)); 
	//printf("read_status = %zi", read(fd, buffer, BUFFER_SIZE));
	return (0);
}