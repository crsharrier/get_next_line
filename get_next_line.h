/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:14:55 by crsharrier        #+#    #+#             */
/*   Updated: 2023/12/01 08:47:16 by crsharrier       ###   ########.fr       */
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

typedef struct s_Gnl
{
	char	**extra_chars;
	char	*buffer;
	char	*line;
	int		read_status;
	int		fd;
	int		buf_len;
	int		nl_index;
	bool	nl_found;
	bool	extra_exists;
}				t_Gnl;

char	*get_next_line(int fd);
void	*gnl_bzero(void *s, int n);
void	*gnl_free_and_replace(char **old, char *new);
void	init_gnl(int fd, char **extra_chars, t_Gnl *gnl);

#endif