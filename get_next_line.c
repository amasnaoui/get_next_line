/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasnaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:49:27 by amasnaou          #+#    #+#             */
/*   Updated: 2021/12/05 14:49:31 by amasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find(char *str, int *count)
{
	int	i;

	i = -1;
	*count = 0;
	while (str[++i])
		if (str[i] == '\n')
		{
			*count++;
			return (1);
		}
	return (0);
}

char *get_line(int fd, int *count)
{
	char	*buffer;
	char	*line;
	int	read_test;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	line = "\0";
	while (!find(line,count))
	{
		read_test = read (fd, buffer, BUFFER_SIZE);
		buffer[read_test] = '\0';
		if (read_test == -1)
		{
			free(buffer);
			return (NULL);
		}
		line = ft_strjoin(line, buffer);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	int	count;
	char	*line;
	static char	*rest;

	if (!find(rest, &count))
	{
		rest = ft_strjoin(rest, get_line(fd, &count));
	}
	else
	{
		line = (char *)malloc(count + 1);
		line = ft_substr(rest, 0, count);
		rest = ft_substr(rest, count, ft_strlen(rest) - count);
	}
	return (line);
}
int main()
{
	int fd = open("test.txt", O_RDONLY);
	printf("%s",get_next_line(fd));
}