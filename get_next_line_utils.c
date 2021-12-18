/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasnaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:50:04 by amasnaou          #+#    #+#             */
/*   Updated: 2021/12/05 14:50:06 by amasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len;
	char	*p;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2));
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (s1[++i])
	{
		*p = s1[i];
		p++;
	}
	i = -1;
	while (s2[++i])
	{
		*p = s2[i];
		p++;
	}
	*p = 0;
	return (p - len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	lenstring;
	char	*p;

	i = 0;
	if (!s)
		return (0);
	lenstring = ft_strlen(s);
	if (start >= lenstring)
		return (ft_strdup("\0"));
	if (start + len >= lenstring)
		p = (char *)malloc(lenstring - start + 1);
	else
		p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	while (s[start] && i < len)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}