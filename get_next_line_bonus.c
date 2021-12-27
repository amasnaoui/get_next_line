/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasnaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:56:00 by amasnaou          #+#    #+#             */
/*   Updated: 2021/12/26 16:56:02 by amasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	i;

	i = 0;
	p = malloc(count * size + 1);
	if (!p)
		return (NULL);
	while (i < count * size + 1)
	{
		((unsigned char *)p)[i] = 0;
		i++;
	}
	return (p);
}

int	find(char *str, int *count)
{
	int	i;

	i = -1;
	*count = 0;
	if (!str)
		return (0);
	while (str[++i])
	{
		(*count)++;
		if (str[i] == '\n')
			return (1);
	}
	return (0);
}

char	*get_line(int fd, int *count, char *rest)
{
	char	*buffer;
	int		read_test;

	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	read_test = 1;
	while (!find(rest, count) && read_test != 0)
	{
		read_test = read (fd, buffer, BUFFER_SIZE);
		if (read_test < 0 || !*buffer)
			return (free(buffer), free(rest), NULL);
		buffer[read_test] = '\0';
		if (!rest && read_test != 0)
			rest = ft_strdup(buffer);
		else if (rest && read_test != 0)
			rest = ft_strjoin(rest, buffer);
	}
	free(buffer);
	if (read_test == 0 && *rest == '\0')
		return (free(rest), NULL);
	return (rest);
}

char	*get_next_line(int fd)
{
	int			count;
	char		*line;
	static char	*rest[1024];

	count = 0;
	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	if (!find(rest[fd], &count))
		rest[fd] = get_line(fd, &count, rest[fd]);
	if (rest[fd] == NULL)
		return (NULL);
	line = ft_substr(rest[fd], 0, count);
	rest[fd] = ft_strdup2(rest[fd], rest[fd] + (count));
	return (line);
}

int main()
{
	int fd = open("test1.txt", O_RDONLY);
	int fd1 = open("test2.txt", O_RDONLY);
	// int fd2 = open("test3.txt", O_RDONLY);
	char *line;
	line = get_next_line(fd);
	printf("%s",line);
	line = get_next_line(fd1);
	printf("%s",line);
	line = get_next_line(fd);
	printf("%s",line);
	line = get_next_line(fd);
	printf("%s",line);
	line = get_next_line(fd1);
	printf("%s",line);
	// while (line)
	// {
	// 	printf("%s",line);
	// 	line = get_next_line(fd);
	// }
}
