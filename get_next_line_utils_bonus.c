/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jknyzhen <jknyzhen@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:46:00 by jknyzhen          #+#    #+#             */
/*   Updated: 2023/03/22 15:37:32 by jknyzhen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	ft_memset(char *s, char c, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		s[i] = c;
		i++;
	}
}

void	add_chunk_to_line(char **line, char *chunk, int chunk_len)
{
	int			iterator;
	int			line_len;
	char		*tmp;

	iterator = 0;
	if (*line == NULL)
		line_len = 0;
	else
		line_len = ft_strlen(*line);
	tmp = *line;
	*line = malloc(sizeof(char) * (chunk_len + line_len + 1));
	while (iterator < line_len)
	{
		(*line)[iterator] = tmp[iterator];
		iterator++;
	}
	if (line_len)
		free(tmp);
	iterator = 0;
	while (line_len + iterator < chunk_len + line_len)
	{
		(*line)[line_len + iterator] = chunk[iterator];
		iterator++;
	}
	(*line)[line_len + iterator] = '\0';
}
