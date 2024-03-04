/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:16:55 by lodemetz          #+#    #+#             */
/*   Updated: 2023/11/24 17:21:07 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == uc)
			return ((char *)s);
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char			*str;
	unsigned int	i;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
	{
		if (s1)
			free(s1);
		return (0);
	}
	i = 0;
	if (s1)
	{
		while (*s1)
			str[i++] = *s1++;
		free(s1 - i);
	}
	if (s2)
	{
		while (*s2)
			str[i++] = *s2++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(const char *s)
{
	char			*sdup;
	unsigned int	i;

	if (!*s)
		return (0);
	sdup = malloc(ft_strlen(s) + 1);
	if (!sdup)
		return (0);
	i = 0;
	while (s[i])
	{
		sdup[i] = s[i];
		i++;
	}
	sdup[i] = '\0';
	return (sdup);
}
