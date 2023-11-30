#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include <string.h>
#include <time.h>


void	test_helpers()
{

	printf("\n===== TEST SPLIT =====\n");
	char *split_str1 = "Hello\nWorld";
	char *split_str2 = "";
	char *split_str3 = "Hello";
	char *split_str4 = "\n";
	char *split_result = NULL;
/*
	split(split_str1, &split_result, false);
	printf("First half of %s = %s\n", split_str1, split_result);
	split(split_str1, &split_result, true);
	printf("Second half of %s = %s\n", split_str1, split_result);
	split(split_str2, &split_result, false);
	printf("First half of %s = %s\n", split_str2, split_result);
	split(split_str2, &split_result, true);
	printf("Second half of %s = %s\n", split_str2, split_result);

	split(split_str3, &split_result, false);
	printf("First half of %s = %s\n", split_str3, split_result);
	split(split_str3, &split_result, true);
	printf("Second half of %s = %s\n", split_str3, split_result);

	split(split_str4, &split_result, false);
	printf("First half of %s = %s\n", split_str4, split_result);
	split(split_str4, &split_result, true);
	printf("Second half of %s = %s\n", split_str4, split_result);
*/

/*
	printf("\n===== TEST STRAPPEND =====\n");
	char	*suffix = strdup("World");
	char	*str = strdup("Hello");
	printf("str before = %s\n", str);
	strappend(suffix, &str);
	printf("str after = %s\n", str);
	printf("\n");

	free(str);
	str = malloc(sizeof(char));
	str[0] = '\0';
	printf("str before = %s\n", str);
	strappend(suffix, &str);
	printf("str after = %s\n", str);
*/

/*
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
	if (!result)
	{
		printf("Either READ ERROR or File \"%s\" is empty!\n", filename);
		return ;
	}
	int	i = 1;
	while(result)
	{
		printf("\033[0;32m%i ->\033[0m", i);
		printf("%s", result);
		result = get_next_line(fd);
		i++;
	}
	printf("\033[0;32m%i ->\033[0m", i);
	printf("%s", result);
	printf("============================================================\n");
}

int main(void)
{
	char	*testfile = "testfiles/multiple_nlx5";
	//char	*testfile = "testfiles/43_with_nl";
	char	*status;
	int		fd;
	int		c;

	//test_helpers();

	fd = open(testfile, O_RDONLY);
	
	//TEST A SINGLE GNL() CALL
	//printf("result = %s\n", get_next_line(fd));


	clock_t t; 
    t = clock(); 

	printf("Testfile = %s\n", testfile);
	test_filename(testfile);

    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; 
	printf("get_next_line() took %f seconds to execute \n", time_taken); 

	close(fd);
	return (0);
}