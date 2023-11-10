/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <csharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:14:55 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/10 16:33:53 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

int		ft_strlen(char *str);
char	*get_next_line(int fd);
char	*ft_substrp(char *s, char *p);
char	*ft_strchr(const char *s, int c);
void	ft_psubstr(char **s, char *p);
void	ft_strappend(char *suffix, char **str);

#endif