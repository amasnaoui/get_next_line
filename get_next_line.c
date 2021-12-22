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
	if (str[++i] == '\n')
		i++;
	while (str[++i])
	{
		(*count)++;
		if (str[i] == '\n')
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
	if (!buffer)
		return (NULL);
	line = "\0";
	read_test = 1;
	while (!find(line, count) && read_test != 0)
	{
		read_test = read (fd, buffer, BUFFER_SIZE);
		if (read_test < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_test] = '\0';
		line = ft_strjoin(line, buffer);
	}
	if (read_test == 0 && *line == '\0')
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	int	count;
	char	*line;
	static char	*rest = "\0";
	int	rlen;

	if(BUFFER_SIZE <= 0 || read(fd,NULL,0) < 0)
		return(NULL);
	count = 0;
	rlen = ft_strlen(rest);
	/*if(!get_line(fd, &count))
		return(NULL);*/
	if (find(rest, &count) == 0)
		rest = ft_strjoin(rest, get_line(fd, &count));
	line = (char *)malloc(count + rlen + 1);
	if (!line)
		return (NULL);
	line = ft_substr(rest, 0, count + rlen + 1);
	rest = ft_substr(rest, count + rlen + 1, ft_strlen(rest) - count + rlen);
	return (line);
}

// int main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *line;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s",line);
// 		line = get_next_line(fd);
// 	}
// }