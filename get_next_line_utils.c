/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <csharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:10:27 by crsharrier        #+#    #+#             */
/*   Updated: 2023/12/01 10:02:40 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Initializes gnl struct. 
	All of the below is done ONCE at the start of gnl():

Allocates space on the heap for the buffer and zeroes the memory.
If anything is found in extra_chars, extra_exists is set to true.
*/
void	init_gnl(int fd, char **extra_chars, t_Gnl *gnl)
{
	gnl->fd = fd;
	gnl->buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	gnl_bzero(gnl->buffer, BUFFER_SIZE + 1);
	gnl->line = NULL;
	gnl->read_status = 0;
	gnl->nl_found = false;
	gnl->nl_index = 0;
	gnl->extra_chars = extra_chars;
	gnl->extra_exists = false;
	if (*extra_chars && (*extra_chars)[0])
		gnl->extra_exists = true;
}

/*
Frees a char pointer and replaces it with a new one.
Checks that *old is not null before freeing the old pointer
	thus, should be only passed a malloc'd or NULL pointer.
*/
void	*gnl_free_and_replace(char **old, char *new)
{
	if (*old)
		free(*old);
	*old = new;
	return (NULL);
}

/*
Set to zero:
	n consecutive bytes, starting at s.
*/
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