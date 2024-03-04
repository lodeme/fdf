/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:06:43 by lodemetz          #+#    #+#             */
/*   Updated: 2023/11/25 14:01:41 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_buffer(char *line, char *buffer)
{
	free(line);
	free(buffer);
	return (0);
}

char	*read_line(int fd, char *line)
{
	char	*buffer;
	ssize_t	bytesread;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_buffer(line, buffer));
	while (!ft_strchr(line, '\n'))
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
			return (free_buffer(line, buffer));
		if (bytesread == 0)
			break ;
		buffer[bytesread] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*get_remainder(char *line)
{
	char	*newline;
	char	*remainder;

	newline = ft_strchr(line, '\n');
	if (newline++)
	{
		remainder = ft_strdup(newline);
		*newline = '\0';
	}
	else
		remainder = 0;
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	line = read_line(fd, remainder);
	remainder = get_remainder(line);
	return (line);
}
