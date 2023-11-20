/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:10:27 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/20 10:20:19 by crsharrier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str, bool limit_nl)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (limit_nl)
		{
			if(str[i] == '\n')
				return (i + 1);
		}
		i++;
	}
	return (i);
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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	while(src[len++]);
	len--;
	if (!size)
		return (len);
	i = 0;
	while (i++ < (size - 1) && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (len);
}

/*
Frees dest if not null.
Assigns result to *dest.
*/
void	substr_alloc(char **dest, char *result)
{
	if (*dest)
		free(*dest);
	*dest = result;
}

/*
Appends suffix to the end of *chars_read.
*/
void	ft_strappend(char *suffix, char **chars_read)
{
	int		i;
	int		j;
	char	*result;

	i = ft_strlen(*chars_read, false) + ft_strlen(suffix, true);
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
		j++;
	}
	substr_alloc(chars_read, result);
}

/*
Modifies string literal at **chars_read to only contain chars from newline until the end.
*/
void	ft_psubstr(char **chars_read)
{
	int		i;
	int		j;
	int		start;
	char	*result;

	i = 0;
	while ((*chars_read)[i] && (*chars_read)[i] != '\n')
		i++;
	if (!(*chars_read)[i])//no newline was found
	{
		//*status = 0;
		return ;
	}
	start = i + 1;
	i = 0;
	while ((*chars_read)[i])
		i++;
	result = malloc(sizeof(char) * (i + 1));
	result[i] = '\0';
	j = 0;
	while (j < i)
	{
		result[j] = (*chars_read)[j + start];
		j++;
	}
	if (*result)
		substr_alloc(chars_read, result);
	else
	{
		substr_alloc(chars_read, NULL);
		free(result);
	}
}


void	ft_split(char *str, char **dest, bool second_half)
{
	char	*part1;
	char	*part2;
	int		len1;
	int		len2;

	if (!str[0])
		return (substr_alloc(dest, NULL));
	len1 = 0;
	while ((str)[len1] && (str)[len1] != '\n')
		len1++;
	//len1 = ft_strlen(str, true);
	if (!second_half)
	{
		part1 = calloc(len1 + 2, sizeof(char));
		ft_strlcpy(part1, str, len1 + 2);
		substr_alloc(dest, part1);
		//FREE PART1?
		//free(part1);
		return ;
	}
	else
	{
		len2 = len1;
		if (!str[len2])
			return ;
		len2 = ft_strlen(str + len1 + 1, false);
		part2 = calloc(len2 + 1, sizeof(char));
		ft_strlcpy(part2, str + len1, len2 + 1);
		substr_alloc(dest, part2);
		return ;
	}	
}

/*
Returns a substring of chars_read, from the start until newline, inclusive.
*/
char	*ft_substrp(char **chars_read)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	while ((*chars_read)[i] && (*chars_read)[i] != '\n')
		i++;
	if (!(*chars_read)[i])
		return (NULL); //means newline wasnt found
	result = malloc(sizeof(char) * (i + 2));
	result[i + 1] = '\0';
	j = 0;
	while (j <= i)
	{
		result[j] = (*chars_read)[j];
		j++;
	}
	return (result);
}
