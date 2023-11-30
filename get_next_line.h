/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <csharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:14:55 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/30 16:45:47 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_Mem
{
	char	**extra_chars;
	char	*buffer;
	char	*line;
	int		status;
	int		fd;
	int		buf_len;
	int		nl_index;
	bool	nl_found;
	bool	extra_exists;
}				t_Mem;

char	*get_next_line(int fd);
char	*exit_gnl(t_Mem *mem, char *rtrn);
void	*gnl_bzero(void *s, int n);
void	*gnl_freeplace(char **old, char *new);
void	init_gnl(int fd, char **extra_chars, t_Mem *mem);

#endif