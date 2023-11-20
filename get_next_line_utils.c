/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crsharrier <crsharrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:10:27 by crsharrier        #+#    #+#             */
/*   Updated: 2023/11/20 16:47:47 by crsharrier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*Returns a pointer to the first occurence of c in s*/
char	*gnl_strchr(const char *s, int c)
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
Returns length of a string.
If limit_nl == true, chars are counted up to and including a newline char.
*/
int	gnl_strlen(char *str, bool limit_nl)
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

size_t	gnl_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len])
		len++;
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
void	gnl_free_assign(char **dest, char *result)
{
	if (*dest)
		free(*dest);
	*dest = result;
}

void	*gnl_calloc(size_t nmemb, size_t size)
{
	unsigned long long	intended_size;
	unsigned long long	i;
	void				*result;
	unsigned char		*p;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((unsigned long long)nmemb > ULLONG_MAX / (unsigned long long)size)
		return (NULL);
	intended_size = nmemb * size;
	result = malloc(intended_size);
	if (result == NULL)
		return (result);
	p = result;
	i = 0;
	while (i < intended_size)
		p[i++] = 0;
	return (result);
}