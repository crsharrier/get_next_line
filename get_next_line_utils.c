/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <csharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:10:27 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/14 12:40:36 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str, int limit_nl)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (limit_nl && str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

/*
Takes a pointer to a string literal.
Appends suffix to the end of *str.
*/
void	ft_strappend(char *suffix, char **chars_read)
{
	int		i;
	int		j;
	char	*result;

	i = ft_strlen(*chars_read, 0) + ft_strlen(suffix, 1);
	result = malloc(sizeof(char) * (i + 1));
	result[i] = '\0';
	i = 0;
	if (*chars_read)
	{
		while ((*chars_read)[i])
		{
			result[i] = (*chars_read)[i];
			i++;
		}
	}
	j = 0;
	while (suffix[j])
	{
		result[i++] = suffix[j];
		if (suffix[j++] == '\n')
			break ;
	}
	if (*chars_read)
		free(*chars_read);
	*chars_read = result;
}

void	substr_alloc(char **s, char *result)
{
	free(*s);
	*s = result;
}

/*
Modifies string literal at **s to only contain chars from p until the end.
*/
void	ft_psubstr(char **s, char *p)
{
	int		i;
	int		j;
	int		start;
	char	*result;

	i = 0;
	while ((*s)[i] && (*s) + i != p)
		i++;
	if (!*(*s + i))
		return ;
	i++;
	start = i;
	i = 0;
	while (*(*s + i))
		i++;
	result = malloc(sizeof(char) * (i + 1));
	result[i] = '\0';
	j = 0;
	while (j < i)
	{
		result[j] = *(*s + j + start);
		j++;
	}
	substr_alloc(s, result);
}

/*Returns a pointer to the first occurence of c in s*/
char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*p)
	{
		if (*p == c)
			return (p);
		p++;
	}
	return (NULL);
}
