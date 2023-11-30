/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:14:14 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/29 17:57:52 by crsharrier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Copies leftover chars from mem->buffer to mem->line. 
Copies from newline + 1 until end of buffer.
*/
void	copy_extra(t_Mem *mem)
{
	char	*extra;
	int		i;
	int		j;

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
	if (*(mem->extra_chars))
		free(*(mem->extra_chars));
	*(mem->extra_chars) = extra;
}

/*
Append mem->buffer[0:end] to the end of mem->line
*/
static void	append(t_Mem *mem, int end)
{
	int 	i;
	int		j;
	char	*new_str;
	
	i = 0;
	while (mem->line[i])
		i++;
	new_str = malloc(sizeof(char) * (i + end));
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
	free(mem->line);
	mem->line = new_str;
}

/*
Searches for first occurrence of '\n' in mem->buffer.
Sets nl_index accordingly.
*/
static void    find_newline(t_Mem *mem)
{
	int     i;

	i = 0;
	mem->nl_index = 0;
	mem->nl_found = false;
	while (mem->buffer[i])
	{
		if (mem->buffer[i] == '\n')
		{
			mem->nl_index = i;
			mem->nl_found = true;
			return ;
		}
		i++;
	}
}

/*
Copies mem->buffer into mem->line.
Adds BUFFER_SIZE at a time until newline is found or nothing to read.
If nl_found, copies up to nl_index (inclusive) to mem->line, and copies extra to extra_chars.
*/
static void	iterate(t_Mem *mem)
{
	int		i;
	int		end;

	while (mem->status && !mem->nl_found)
	{
		find_newline(mem);
		end = BUFFER_SIZE;
		if (mem->nl_found)
			end = mem->nl_index + 1;
		append(mem, end);
		if (!mem->nl_found)
		{
			free(mem->buffer);
			mem->buffer = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
			mem->status = read(mem->fd, mem->buffer, BUFFER_SIZE);
		}
	}
	if (mem->nl_found && mem->nl_index != BUFFER_SIZE - 1)
		copy_extra(mem);
}

/*
Performs first read() call, setting status and then calling iterate().
*/
char    *get_next_line(int fd)
{
	t_Mem           mem;
	static char     *extra_chars = NULL;

	mem.fd = fd;
	mem.extra_chars = &extra_chars;
	mem.buffer = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	mem.status = read(fd, mem.buffer, BUFFER_SIZE);
	if (!mem.status)
	{
		if (extra_chars)
			(extra_chars);
		return (extra_chars = NULL);
	}
	if (extra_chars)
		mem.line = strdup(extra_chars);
	else
	{
		mem.line = malloc(sizeof(char) * 1);
		mem.line[0] = '\0';
	}
	iterate(&mem);
	free_memory(&mem);
}