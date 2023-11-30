/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:14:18 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/24 14:18:13 by crsharrier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Appends str1 (from start until \n) to the end of *str2.
*/
static void	strappend(char *str1, char **str2)
{
	int		len;
	int		i;
	int		j;
	char	*result;

	len = gnl_strlen(str1, true) + gnl_strlen(*str2, false);
	result = malloc(sizeof(char) * len + 1);
	result[len] = '\0';
	i = 0;
	if (*str2)
	{
		while ((*str2)[i])
		{
			result[i] = (*str2)[i];
			i++;
		}
	}
	j = 0;
	while (i < len)
		result[i++] = str1[j++];
	free(*str2);
	*str2 = result;
}

/*
Splits str in half at the given index.
If second_half == false, returns first half.
Else, returns second half, starting from index + 1.
Assigns the result to *dest.
*/
void	split(char *str, char **dest, t_Mem *mem, bool second_half)
{
	char	*result;
	int		len2;

	if (!str[0])
		return (gnl_free_assign(dest, NULL));
	if (!second_half)
	{
		result = gnl_calloc(mem->len1 + 2, sizeof(char));
		gnl_strlcpy(result, str, mem->len1 + 2);
		gnl_free_assign(dest, result);
	}
	else
	{
		if (!str[mem->len1])
		{
			gnl_free_assign(dest, NULL);
			return ;
		}	
		len2 = gnl_strlen(str + mem->len1 + 1, false);
		result = gnl_calloc(len2 + 2, sizeof(char));
		gnl_strlcpy(result, str + mem->len1 + 1, len2 + 1);
		gnl_free_assign(dest, result);
	}	
}


/*
Reads into buffer.
Calls read() repeatedly until newline is contained within contents of a read.
*/
static ssize_t	search_newline(int fd, t_Mem *mem)
{
	ssize_t	status;
	bool	nl_found;
	int		i;

	status = 1;
	nl_found = false;
	while (!nl_found && status)
	{
		if (!mem->buffer[0])
			status = read(fd, mem->buffer, BUFFER_SIZE);
		if (status == -1 || status == 0)
			return (status);
		if (status != BUFFER_SIZE)
			mem->buffer[status] = '\0';
		strappend(mem->buffer, &mem->temp);
		i = 0;
		while (mem->temp[i] && !mem->len1)
		{
			if (mem->temp[i] == '\n')
				mem->len1 = i;
			i++;
		}
		if (status != BUFFER_SIZE)
			return (status);
		//newline = gnl_strchr(*temp, '\n');
		
	}
	return (status);
}

/*
Frees and sets to NULL all variables in mem struct.
Returns NULL.
*/
static char	*free_mem(t_Mem *mem)
{
	free(mem->buffer);
	mem->buffer = NULL;
	free(mem->temp);
	mem->temp = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{

	static ssize_t	status = 1;
	static char		*chars_read = NULL;
	t_Mem			mem;
	int 			index;
	
	if (!status)
		return (NULL);
	mem.buffer = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	mem.temp = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (mem.buffer == NULL || mem.temp == NULL)
		return (NULL);
	mem.line = NULL;
	if (chars_read)
		mem.buffer[0] = chars_read[0];
	status = search_newline(fd, &mem);
	if ((!status && !mem.temp && !chars_read) || status == -1)
		return (free_mem(&mem));
	strappend(mem.temp, &chars_read);
	split(chars_read, &mem.line, &mem, false);
	if (mem.line == NULL && *chars_read)
		mem.line = chars_read;
	split(mem.buffer, &chars_read, &mem, true);	
	free_mem(&mem);
	return (mem.line);
}