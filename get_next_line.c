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
	if(!str)
		return (0);
	// if (str[++i] == '\n')
	// 	i++;
	while (str[++i])
	{
		(*count)++;
		if (str[i] == '\n')
			return (1);
	}
	return (0);
}

char *get_line(int fd, int *count, char *rest)
{
	char	*buffer;
	int	read_test;

	buffer = (char *)calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (NULL);
	read_test = 1;
	while (!find(rest, count) && read_test != 0)
	{
		read_test = read (fd, buffer, BUFFER_SIZE);
		if (read_test < 0 || !*buffer)
		{
			free(buffer);
			free(rest);
			return (NULL);
		}
		//buffer[read_test] = '\0';
		if(!rest && read_test != 0)
			rest = ft_strdup(buffer);
		else if(rest && read_test != 0)
			rest = ft_strjoin(rest, buffer);
	}
	free(buffer);
	if (read_test == 0 && *rest == '\0')
	{
		free(rest);
		return (NULL);
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	int	count;
	char	*line;
	static char	*rest;
	if(BUFFER_SIZE <= 0 || read(fd,NULL,0) < 0)
		return(NULL);
	count = 0;
	if (!find(rest, &count))
		rest = get_line(fd, &count, rest);
	if (rest == NULL)
		return (NULL);
	line = ft_substr(rest, 0, count + 1);
	rest = ft_strdup2(rest, rest + (count + 1));
	
	return (line);
}

int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *line;
	line = get_next_line(fd);
	while (line)
	{
		printf("%s",line);
		line = get_next_line(fd);
	}
}
