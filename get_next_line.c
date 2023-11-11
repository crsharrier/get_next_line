/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <csharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:14:18 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/11 12:13:04 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Returns a substring of s, from the start until p.
*/
char	*ft_substrp(char *s, char *p)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	while (s[i] && (s + i) != p)
		i++;
	if (!s[i])
		return (NULL);
	result = malloc(sizeof(char) * (i + 1));
	result[i] = '\0';
	j = 0;
	while (j < i)
	{
		result[j] = s[j];
		j++;
	}
	return (result);
}

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

ssize_t	search_newline(int fd, char **chars_read, char **buffer, char **newline)
{
	ssize_t	status;

	status = 1;
	while (!(*newline) && status)
	{
		status = read(fd, *buffer, BUFFER_SIZE);
		if (status == -1 || status == 0)
			return (status);
		else if (status != BUFFER_SIZE)
			(*buffer)[status] = '\0';
		ft_strappend(*buffer, chars_read);
		*newline = ft_strchr(*chars_read, '\n');
	}
	return (status);
}

void	free_buffer(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
}

char	*get_next_line(int fd)
{
	static ssize_t	status = 1;
	static char		*chars_read;
	char			*buffer;
	char			*substr;
	char			*newline;

	if (!status)
		return (NULL);
	newline = NULL;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	status = search_newline(fd, &chars_read, &buffer, &newline);
	if ((!status && !chars_read) || status == -1)
	{
		free_buffer(&buffer);
		return (NULL);
	}
	substr = ft_substrp(chars_read, newline);
	if (substr == NULL)
		substr = chars_read;
	ft_psubstr(&chars_read, newline);
	free_buffer(&buffer);
	return (substr);
}
