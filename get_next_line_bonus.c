/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:48:07 by obouadel          #+#    #+#             */
/*   Updated: 2021/11/16 16:37:12 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#define MAX_FD 65535

void	ft_free(char *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

char	*ft_line(char **line, char **s_text)
{
	char	*forfree;
	int		tillnl;

	tillnl = 0;
	forfree = *s_text;
	while ((*s_text)[tillnl] != '\n' && (*s_text)[tillnl] != '\0')
		tillnl++;
	if (ft_strchr(*s_text, '\n'))
	{
		*line = ft_substr(*s_text, 0, tillnl + 1);
		*s_text = ft_strdup(*s_text + tillnl + 1);
	}
	else
	{
		*line = ft_strdup(forfree);
		*s_text = NULL;
	}
	ft_free(forfree);
	return (*line);
}

int	ft_fileread(int fd, char **buffer, char **s_text, char **line)
{
	char	*forfree;
	int		bytes;

	bytes = 1;
	while (!ft_strchr(*s_text, '\n') && bytes)
	{
		bytes = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[bytes] = '\0';
		forfree = *s_text;
		*s_text = ft_strjoin(*s_text, *buffer);
		ft_free(forfree);
	}
	ft_free(*buffer);
	ft_line(line, s_text);
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	*s_text[MAX_FD];
	char		*line;
	char		*buffer;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1048)
		return (NULL);
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (read(fd, buffer, 0) < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (!s_text[fd])
		s_text[fd] = ft_strdup("");
	bytes = ft_fileread(fd, &buffer, &s_text[fd], &line);
	if (bytes == 0 && *line == '\0')
	{
		ft_free(line);
		return (NULL);
	}
	return (line);
}
