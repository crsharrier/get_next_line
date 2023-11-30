/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <csharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:14:14 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/30 16:46:10 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Copies leftover chars from mem->buffer to mem->line. 
Copies from newline + 1 until end of buffer.
*/
static void	copy_extra(t_Mem *mem)
{
	char	*extra;
	int		i;

	i = 0;
	while (mem->buffer[mem->nl_index + i + 1])
		i++;
	extra = malloc(sizeof(char) * i + 1);
	extra[i] = '\0';
	i = 0;
	while (mem->buffer[mem->nl_index + i + 1])
	{
		extra[i] = mem->buffer[mem->nl_index + i + 1];
		i++;
	}
	gnl_freeplace(mem->extra_chars, extra);
}

/*
Append mem->buffer[0:end] to the end of mem->line
*/
static void	append(t_Mem *mem, int end)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (mem->line[i])
		i++;
	new_str = malloc(sizeof(char) * (i + end + 1));
	new_str[i + end] = '\0';
	i = 0;
	while (mem->line[i])
	{
		new_str[i] = mem->line[i];
		i++;
	}
	j = 0;
	while (j < end)
		new_str[i++] = mem->buffer[j++];
	gnl_freeplace(&mem->line, new_str);
}

/*
Searches for first occurrence of '\n' in mem->buffer.
Sets nl_index accordingly.
Returns the index of '\n' or '\0', whichever is found first.
*/
static int	find_newline(t_Mem *mem)
{
	int	i;

	i = 0;
	while (mem->buffer[i])
	{
		if (mem->buffer[i] == '\n')
		{
			mem->nl_index = i;
			mem->nl_found = true;
			return (i);
		}
		i++;
	}
	return (i);
}

static void	iterate(t_Mem *mem)
{
	int		end;

	while (!mem->nl_found)
	{
		end = find_newline(mem);
		if (mem->nl_found)
			end = mem->nl_index + 1;
		append(mem, end);
		if (!mem->nl_found)
		{
			gnl_bzero(mem->buffer, BUFFER_SIZE + 1);
			mem->status = read(mem->fd, mem->buffer, BUFFER_SIZE);
			if (!mem->status)
				break ;
		}
	}
	if (mem->nl_found && mem->buffer[mem->nl_index + 1])
		copy_extra(mem);
	else
		gnl_freeplace(mem->extra_chars, NULL);
}

/*
If extra_exists, populate buffer with extra_chars and don't read 
Exit if there are no extra chars and status = 0
Else, iterate()
*/
char	*get_next_line(int fd)
{
	t_Mem		mem;
	static char	*extra_chars = NULL;
	int			i;

	init_gnl(fd, &extra_chars, &mem);
	if (mem.extra_exists)
	{
		gnl_bzero(mem.buffer, BUFFER_SIZE + 1);
		i = 0;
		while (extra_chars[i])
		{
			mem.buffer[i] = extra_chars[i];
			i++;
		}
	}
	else
		mem.status = read(fd, mem.buffer, BUFFER_SIZE);
	if ((mem.status == 0 || mem.status == -1) && !mem.extra_exists)
	{
		gnl_freeplace(&extra_chars, NULL);
		return (exit_gnl(&mem, NULL));
	}
	mem.line = gnl_bzero(malloc(sizeof(char)), 1);
	iterate(&mem);
	return (exit_gnl(&mem, mem.line));
}
