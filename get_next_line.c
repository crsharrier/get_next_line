/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <csharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:14:18 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/10 19:09:09 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	search_newline(int fd, char **chars_read, char **buffer, char **newline)
{
	size_t	status;

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
		//printf("*buffer = %s, *chars_read = %s\n", *buffer, *chars_read);
	}
	return (status);
}

char	*get_next_line(int fd)
{
	static char		*chars_read;
	static size_t	status = 1;
	char			*buffer;
	char			*substr;
	char			*newline;

	if (!status)
		return (NULL);
	newline = NULL;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1)); 
	buffer[BUFFER_SIZE] = '\0';	
	status = search_newline(fd, &chars_read, &buffer, &newline);
	//printf("status = %zi, chars_read = %s\n", status, chars_read);
	if (!status && !chars_read)
		return (NULL);
	if (status == -1)
	{
		free(buffer);
		return (NULL);
	}
	substr = ft_substrp(chars_read, newline);
	if (substr == NULL)
		substr = chars_read;
	ft_psubstr(&chars_read, newline);
	free(buffer);
	buffer = NULL;
	return (substr);
}
