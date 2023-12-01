/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <csharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:14:14 by crsharrier        #+#    #+#             */
/*   Updated: 2023/12/01 10:52:08 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Copies leftover chars from gnl->buffer to gnl->line. 
Copies from newline + 1 until end of buffer.
*/
static void	_copy_extra_chars(t_Gnl *gnl)
{
	char	*extra;
	int		i;

	i = 0;
	while (gnl->buffer[gnl->nl_index + i + 1])
		i++;
	extra = malloc(sizeof(char) * i + 1);
	extra[i] = '\0';
	i = 0;
	while (gnl->buffer[gnl->nl_index + i + 1])
	{
		extra[i] = gnl->buffer[gnl->nl_index + i + 1];
		i++;
	}
	gnl_free_and_replace(gnl->extra_chars, extra);
}

/*
Append gnl->buffer([0:end], non-inclusive) to the end of gnl->line.

If gnl->line == NULL, neither while loop will execute
	and gnl->line will be created instead of extended.
*/
static void	_append_buffer_to_end_of_line(t_Gnl *gnl, int end)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (gnl->line && gnl->line[i])
		i++;
	new_str = malloc(sizeof(char) * (i + end + 1));
	new_str[i + end] = '\0';
	i = 0;
	while (gnl->line && gnl->line[i])
	{
		new_str[i] = gnl->line[i];
		i++;
	}
	j = 0;
	while (j < end)
		new_str[i++] = gnl->buffer[j++];
	gnl_free_and_replace(&gnl->line, new_str);
}

/*
Searches for first occurrence of '\n' in gnl->buffer.
If found, sets nl_index and nl_found.
Returns the index of '\n' or '\0', whichever is found first.
*/
static int	_find_newline_or_null(t_Gnl *gnl)
{
	int	i;

	i = 0;
	while (gnl->buffer[i])
	{
		if (gnl->buffer[i] == '\n')
		{
			gnl->nl_index = i;
			gnl->nl_found = true;
			return (i);
		}
		i++;
	}
	return (i);
}

static void	iterate(t_Gnl *gnl)
{
	int		end;

	while (!gnl->nl_found)
	{
		end = _find_newline_or_null(gnl);
		if (gnl->nl_found)
			end = gnl->nl_index + 1;
		_append_buffer_to_end_of_line(gnl, end);
		if (!gnl->nl_found)
		{
			gnl_bzero(gnl->buffer, BUFFER_SIZE + 1);
			gnl->read_status = read(gnl->fd, gnl->buffer, BUFFER_SIZE);
			if (!gnl->read_status)
				break ;
		}
	}
	if (gnl->nl_found && gnl->buffer[gnl->nl_index + 1])
		_copy_extra_chars(gnl);
	else
		gnl_free_and_replace(gnl->extra_chars, NULL);
}

/*
Main gnl() function.

Initialises gnl struct.

if extra_exists,
	populate buffer with extra_chars and don't read
else,
	read() into buffer

if there are no extra chars and status <= 0,
	return NULL
else,
	iterate()

Iterate populates gnl.line
Free gnl.buffer and return gnl.line.
*/
char	*get_next_line(int fd)
{
	t_Gnl		gnl;
	static char	*extra_chars = NULL;
	int			i;

	init_gnl(fd, &extra_chars, &gnl);
	if (gnl.extra_exists)
	{
		i = 0;
		while (extra_chars[i])
		{
			gnl.buffer[i] = extra_chars[i];
			i++;
		}
	}
	else
		gnl.read_status = read(fd, gnl.buffer, BUFFER_SIZE);
	if ((gnl.read_status <= 0) && !gnl.extra_exists)
	{
		gnl_free_and_replace(&extra_chars, NULL);
		free(gnl.buffer);
		return (NULL);
	}
	iterate(&gnl);
	free(gnl.buffer);
	return (gnl.line);
}
