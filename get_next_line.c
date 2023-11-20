/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:14:18 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/20 16:42:27 by crsharrier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Appends suffix to the end of *chars_read.
*/
static void	strappend(char *suffix, char **chars_read)
{
	int		i;
	int		j;
	char	*result;

	i = gnl_strlen(*chars_read, false) + gnl_strlen(suffix, true);
	result = gnl_calloc(i + 1, sizeof(char));
	i = 0;
	if (*chars_read)
	{
		while ((*chars_read)[i])
		{
			result[i] = (*chars_read)[i];
			i++;
		}
	}
	j = 0;
	while (suffix[j])
	{
		result[i++] = suffix[j];
		j++;
	}
	gnl_free_assign(chars_read, result);
}

/*
Splits str in half at the delimiter.
If second_half == true, returns first half (incl. delimiter)
Else, returns second half, starting from delim + 1. 
*/
static void	split(char *str, char **dest, bool second_half)
{
	char	*part1;
	char	*part2;
	int		len1;
	int		len2;

	if (!str[0])
		return (gnl_free_assign(dest, NULL));
	len1 = 0;
	while ((str)[len1] && (str)[len1] != '\n')
		len1++;
	if (!second_half)
	{
		part1 = gnl_calloc(len1 + 2, sizeof(char));
		gnl_strlcpy(part1, str, len1 + 2);
		gnl_free_assign(dest, part1);
		return ;
	}
	else
	{
		if (!str[len1])
			return ;
		len2 = gnl_strlen(str + len1 + 1, false);
		part2 = gnl_calloc(len2 + 2, sizeof(char));
		gnl_strlcpy(part2, str + len1 + 1, len2 + 1);
		gnl_free_assign(dest, part2);
		return ;
	}	
}


/*
Reads into buffer.
Calls read() repeatedly until newline is contained within contents of a read.
*/
static ssize_t	search_newline(int fd, char **buffer, char **temp)
{
	ssize_t	status;
	char	*newline;

	status = 1;
	newline = NULL;
	while (!newline && status)
	{
		status = read(fd, *buffer, BUFFER_SIZE);
		if (status == -1 || status == 0)
			return (status);
		strappend(*buffer, temp);
		newline = gnl_strchr(*temp, '\n');
		if (status != BUFFER_SIZE)
			return (status);
	}
	return (status);
}

static char	*free_buffer(char **buffer, char **temp)
{
	free(*buffer);
	*buffer = NULL;
	free(*temp);
	*temp = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static ssize_t	status = 1;
	static char		*chars_read = NULL;
	char			*buffer;
	char			*line;
	char			*temp;

	if (!status)
		return (NULL);
	buffer = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	temp = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL || temp == NULL)
		return (NULL);
	line = NULL;

	status = search_newline(fd, &buffer, &temp);
	if ((!status && !temp && !chars_read) || status == -1)
		return (free_buffer(&buffer, &temp));
	strappend(temp, &chars_read);

	split(chars_read, &line, false);
 	//line = ft_substrp(&chars_read);
	if (line == NULL && *chars_read)
		line = chars_read;

	split(chars_read, &chars_read, true);	
	//ft_psubstr(&chars_read);
	free_buffer(&buffer, &temp);
	return (line);
}