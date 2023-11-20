/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:14:18 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/20 10:13:37 by crsharrier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned long long	intended_size;
	unsigned long long	i;
	void				*result;
	unsigned char		*p;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((unsigned long long)nmemb > ULLONG_MAX / (unsigned long long)size)
		return (NULL);
	intended_size = nmemb * size;
	result = malloc(intended_size);
	if (result == NULL)
		return (result);
	p = result;
	i = 0;
	while (i < intended_size)
		p[i++] = 0;
	return (result);
}

/*
Reads into buffer.
Calls read() repeatedly until newline is contained within contents of a read.
*/
ssize_t	search_newline(int fd, char **buffer, char **temp)
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
		ft_strappend(*buffer, temp);
		newline = ft_strchr(*temp, '\n');
		if (status != BUFFER_SIZE)
			return (status);
	}
	return (status);
}

char	*free_buffer(char **buffer, char **temp)
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
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL || temp == NULL)
		return (NULL);
	line = NULL;

	status = search_newline(fd, &buffer, &temp);
	if ((!status && !temp && !chars_read) || status == -1)
		return (free_buffer(&buffer, &temp));
	ft_strappend(temp, &chars_read);

	ft_split(chars_read, &line, false);
 	//line = ft_substrp(&chars_read);
	if (line == NULL && *chars_read)
		line = chars_read;

	ft_split(chars_read, &chars_read, true);	
	//ft_psubstr(&chars_read);
	free_buffer(&buffer, &temp);
	return (line);
}