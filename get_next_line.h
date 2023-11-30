/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:14:55 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/29 17:55:37 by crsharrier       ###   ########.fr       */
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

# include <string.h>


typedef struct  s_Mem
{
	char	**extra_chars;
	char	*buffer;
	char	*line;
	int		status;
	int		fd;
	int		nl_index;
	bool	nl_found;
}				t_Mem;

char	*get_next_line(int fd);
void	*gnl_calloc(size_t nmemb, size_t size);
void	free_memory(t_Mem *mem);
#endif