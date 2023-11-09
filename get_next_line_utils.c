/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:10:27 by crsharrier        #+#    #+#             */
/*   Updated: 2023/10/13 08:05:35 by crsharrier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	strappend(char **str, char *suffix)
{
	int		i;
	int		j;
	char	*result;

	i = ft_strlen(*str);
	j = ft_strlen(suffix);
	result = malloc(sizeof(char) * (i + j + 1));
	result[i + j] = '\0';
	i = 0;
	while ((*str)[i])
	{
		result[i] = (*str)[i];
		i++;
	}
	j = 0;
	while (suffix[j])
	{
		result[i++] = suffix[j];
		j++;
	}
	free(*str);
	*str = result;
}

char	*ft_substrp(char *s, char *p)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	while (s[i] && (s + i) != p)
		i++;
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

char	*ft_psubstr(char *s, char *p)
{
	int		i;
	int		j;
	int		start;
	char	*result;

	i = 0;
	while (s[i] && (s + i) != p)
		i++;
	if (!s[i])
		return (NULL);
	i++;
	start = i;
	j = i;
	i = 0;
	while (s[j++])
		i++;
	result = malloc(sizeof(char) * (i + 1));
	result[i] = '\0';
	j = 0;
	while (j < i)
	{
		result[j] = s[j + start];
		j++;
	}
	return (result);
}

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
	return (p);
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