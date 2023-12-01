/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:10:27 by crsharrier        #+#    #+#             */
/*   Updated: 2023/12/01 08:47:18 by crsharrier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	init_gnl(int fd, char **extra_chars, t_Gnl *gnl)
{
	
	gnl->fd = fd;
	gnl->extra_chars = extra_chars;
	gnl->buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	gnl_bzero(gnl->buffer, BUFFER_SIZE + 1);
	gnl->line = NULL;
	gnl->read_status = 0;
	gnl->nl_found = false;
	gnl->nl_index = 0;
	gnl->extra_exists = false;
	if (*extra_chars && (*extra_chars)[0])
		gnl->extra_exists = true;
}

void	*gnl_free_and_replace(char **old, char *new)
{
	if (*old)
		free(*old);
	*old = new;
	return (NULL);
}

void	*gnl_bzero(void *s, int n)
{
	int				i;
	unsigned char	*p;

	p = s;
	i = 0;
	while (i < n)
		p[i++] = (unsigned char) '\0';
	return (s);
}

/*
char	*gnl_strdup(const char *src)
{
		char	*dest;
		int		i;

		i = 0;
		while (*(src + i))
				i++;
		dest = malloc(sizeof(char) * (i + 1));
		while (i >= 0)
		{
				*(dest + i) = *(src + i);
				i--;
		}
		return (dest);
}
*/