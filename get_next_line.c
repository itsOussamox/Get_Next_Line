/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 05:32:38 by marvin            #+#    #+#             */
/*   Updated: 2021/11/15 05:32:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 100
#define	MAX_FD 5
void	ft_free(char *str)
{
	if(str)
	{
		free(str);
		str = 0;
	}	
}

char	*ft_line(char **line, char **s_tatic)
{
	int		tillnl;
	char	*forfree;

	tillnl = 0;
	while ((*s_tatic)[tillnl] != '\n' && (*s_tatic)[tillnl] != '\0')
		tillnl++;
	forfree = *s_tatic;
	if (ft_strchr(*s_tatic, '\n'))
	{
		*line = ft_substr(*s_tatic, 0, tillnl + 1);
		*s_tatic = ft_strdup(s_tatic + tillnl + 1);
	}
	else
	{
		*line = ft_strdup(forfree);
		*s_tatic = 0;
	}
	ft_free(forfree);
	return (*line);
}
int	ft_fileread(char **line, char **buffer, char **s_tatic, int fd)
{
	int		bytes;
	char	*forfree;

	bytes = 1;
	while (bytes && !ft_strchr(*s_tatic, '\n'))
	{
		bytes = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[BUFFER_SIZE] = '\0';
		forfree = *s_tatic;
		*s_tatic = ft_strjoin(*s_tatic, *buffer);
		ft_free(forfree);
	}
	ft_free(*buffer);
	ft_line(&line, &s_tatic);
	return(bytes);
}

char	*get_next_line(int fd)
{
	static char *s_tatic[MAX_FD];	
	char		*line;
	char		*buffer;
	
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (0);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	if (read(fd, buffer, 0) < 0)
	{
		free(buffer);
		return(0);
	}
	if (!s_tatic[fd])
		s_tatic[fd] = ft_strdup("");
	if (ft_fileread(&line, &buffer, &s_tatic, fd) == 0 || *line == '\0')
	{
		ft_free(buffer);
		return (0);
	}
}