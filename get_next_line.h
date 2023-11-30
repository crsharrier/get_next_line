/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:14:55 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/24 14:16:54 by crsharrier       ###   ########.fr       */
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

typedef struct  s_Mem
{
	char			*buffer;
	char			*line;
	char			*temp;
    int             len1;
}               t_Mem;

char	*get_next_line(int fd);
char	*gnl_strchr(const char *s, int c);
int	    gnl_strlen(char *str, bool limit_nl);
size_t	gnl_strlcpy(char *dst, const char *src, size_t size);
void	gnl_free_assign(char **s, char *result);
void	*gnl_calloc(size_t nmemb, size_t size);

void	split(char *str, char **dest, t_Mem *mem, bool second_half);
#endif