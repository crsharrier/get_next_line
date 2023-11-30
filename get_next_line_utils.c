/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <csharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:10:27 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/30 17:36:31 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	init_gnl(int fd, char **extra_chars, t_Mem *mem)
{
	mem->fd = fd;
	mem->extra_chars = extra_chars;
	mem->buffer = gnl_bzero(malloc(BUFFER_SIZE + 1 * sizeof(char)),
			BUFFER_SIZE + 1);
	mem->line = NULL;
	mem->status = 0;
	mem->nl_found = false;
	mem->nl_index = 0;
	mem->extra_exists = false;
	if (*extra_chars && (*extra_chars)[0])
		mem->extra_exists = true;
}

void	*gnl_freeplace(char **old, char *new)
{
	if (*old)
		free(*old);
	*old = new;
	return (NULL);
}

char	*exit_gnl(t_Mem *mem, char *rtrn)
{
	free(mem->buffer);
	return (rtrn);
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