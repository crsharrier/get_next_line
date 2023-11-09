/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:14:18 by crsharrier        #+#    #+#             */
/*   Updated: 2023/10/13 08:04:30 by crsharrier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*chars_read;
	char		*buffer;
	char		*substr;
	char		*newline;
	int			read_status;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	buffer[BUFFER_SIZE] = '\0';
	chars_read = malloc(sizeof(char));
	chars_read[0] = '\0';
	newline = NULL;
	while (!newline)
	{
		read_status = read(fd, buffer, BUFFER_SIZE);
		if (read_status == -1 || read_status == 0)
			return (NULL);
		else if (read_status != BUFFER_SIZE)
			buffer[read_status] = '\0';
		strappend(&chars_read, buffer);
		newline = ft_strchr(chars_read, '\n');
	}
	substr = ft_substrp(chars_read, newline);
	if (substr == NULL)
		substr = chars_read;
	chars_read = ft_psubstr(chars_read, newline);
	free(buffer);
	return (substr);
}
