/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jknyzhen <jknyzhen@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:24:05 by jknyzhen          #+#    #+#             */
/*   Updated: 2023/03/21 19:34:38 by jknyzhen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*return_line(char *line)
{
	char	*real_line;
	int		line_iterator;

	if (line == NULL)
		return (NULL);
	line_iterator = 0;
	while (line[line_iterator] != '\n')
	{
		if (line[line_iterator] == '\0')
			break ;
		line_iterator++;
	}
	real_line = malloc(sizeof(char) * (line_iterator + 1 + \
	(line[line_iterator] == '\n')));
	line_iterator = 0;
	while (line[line_iterator])
	{
		real_line[line_iterator] = line[line_iterator];
		if (line[++line_iterator - 1] == '\n')
			break ;
	}
	real_line[line_iterator] = '\0';
	free (line);
	return (real_line);
}

static void	save_remainer(char *line, char *remainer)
{
	int	line_iterator;
	int	remainer_iterator;

	line_iterator = 0;
	remainer_iterator = 0;
	if (line == NULL)
		return ;
	while (line[line_iterator] != '\n')
	{
		if (line[line_iterator] == '\0')
			return ;
		line_iterator++;
	}
	line_iterator++;
	while (line[line_iterator])
	{
		remainer[remainer_iterator] = line[line_iterator];
		line_iterator++;
		remainer_iterator++;
	}
}

static int	build_line(int fd, char **line)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_size;

	ft_memset(buffer, 0, BUFFER_SIZE + 1);
	read_size = read(fd, buffer, BUFFER_SIZE);
	if (read_size <= 0)
		return (read_size);
	add_chunk_to_line(line, buffer, read_size);
	return (read_size);
}

static int	line_has_no_newline(char *line)
{
	int	iterator;

	if (line == NULL)
		return (1);
	iterator = 0;
	while (line[iterator])
	{
		if (line[iterator] == '\n')
			return (0);
		iterator++;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	remainer[BUFFER_SIZE + 1];
	char		*line;
	int			read_size;

	if (fd < 0)
		return (NULL);
	line = NULL;
	if (remainer[0] != '\0')
		add_chunk_to_line(&line, remainer, ft_strlen(remainer));
	while (line_has_no_newline(line))
	{
		read_size = build_line(fd, &line);
		if (read_size == 0)
			break ;
		else if (read_size == -1)
		{
			if (line)
				free(line);
			ft_memset(remainer, 0, BUFFER_SIZE + 1);
			return (NULL);
		}
	}
	ft_memset(remainer, 0, BUFFER_SIZE + 1);
	save_remainer(line, remainer);
	return (return_line(line));
}

// #include <stdio.h>

//  int	main(void)
// {
// 	char	*line;
// 	int	fd;

// 	// fd = open("short.txt", O_RDONLY);
// 	while (line)
// 	{
// 		line = get_next_line(10);
// 		printf("%s", line);
// 	}
// 	return (0);
// }