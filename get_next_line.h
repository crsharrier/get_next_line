/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:14:55 by crsharrier        #+#    #+#             */
/*   Updated: 2023/10/13 07:55:21 by crsharrier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

#include<stdlib.h>
#include<unistd.h>

char	*get_next_line(int fd);
char	*ft_substrp(char *s, char *p);
char	*ft_psubstr(char *s, char *p);
char	*ft_strchr(const char *s, int c);
char	*strappend(char **str, char *suffix);

# endif