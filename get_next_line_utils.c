/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <csharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:10:27 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/10 17:23:47 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

/*
Takes a pointer to a string literal.
Appends suffix to the end of *str.
*/
void	ft_strappend(char *suffix, char **str)
{
	int		i;
	int		j;
	char	*result;

	//printf("ft_strlen(*str) = %i\n", ft_strlen(*str));
	i = ft_strlen(*str);
	j = ft_strlen(suffix);
	result = malloc(sizeof(char) * (i + j + 1));
	result[i + j] = '\0';
	i = 0;
	if (*str)
	{
		while ((*str)[i])
		{
			result[i] = (*str)[i];
			i++;
		}
	}
	j = 0;
	while (suffix[j])
	{
		result[i++] = suffix[j];
		j++;
	}
	if (*str)
		free(*str);
	*str = result;
}

/*
Returns a substring of s, from the start until p.
*/
char	*ft_substrp(char *s, char *p)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	while (s[i] && (s + i) != p)
		i++;
	if (!s[i])
		return (NULL);
	result = malloc(sizeof(char) * (i + 1));
	result[i] = '\0';
	j = 0;
	while (j < i)
	{
		result[j] = s[j];
		j++;
	}
	return (result);
}

static void	substr_alloc(char **s, char *result)
{
	free(*s);
	*s = result;
}

/*
Returns a substring of s, from p until the end.
Takes pointer to string literal, to be able to free *s.
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
	j = i;
	i = 0;
	while (*(*s + j++))
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
/*
int main(void)
{
	char *str;
	char *newline;


	str = malloc(sizeof(char) * 13);
	strcpy(str, "hello\nworld\n");
	newline = ft_strchr(str, '\n');

	printf("str = %s\n", str);
	printf("Result for ft_psubstr(str, newline) = %s\n", ft_psubstr(str, newline));
	printf("Result for ft_substrp(str, newline) = %s\n", ft_substrp(str, newline));

	return (0);
}*/