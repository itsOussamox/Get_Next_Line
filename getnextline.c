/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:26:52 by marvin            #+#    #+#             */
/*   Updated: 2021/11/16 11:26:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "getnextline.h"
#include <stdio.h>
#define BUFFER_SIZE 15

void	free_ptr(char *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}


char	*get_line(char **line, char **s_text)
{
	char	*buff_temp;
	int		buff_nl;

	buff_nl = 0;
	buff_temp = *s_text;
	while ((*s_text)[buff_nl] != '\n' && (*s_text)[buff_nl] != '\0')
		buff_nl++;
	if (ft_strchr(*s_text, '\n'))
	{
		*line = ft_substr(*s_text, 0, buff_nl + 1);
		*s_text = ft_strdup(*s_text + buff_nl + 1);
	}
	else
	{
		*line = ft_strdup(buff_temp);
		*s_text = NULL;
	}
	free_ptr(buff_temp);
	return (*line);
}

int	read_file(int fd, char **buffer, char **s_text, char **line)
{
	int		bytes;
	char	*forfree;

	bytes = 1;
	while (!ft_strchr(*s_text, '\n') && bytes)
	{
		bytes = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[bytes] = '\0';
		forfree = *s_text;
		*s_text = ft_strjoin(*s_text, *buffer);
		free_ptr(forfree);
	}
	free_ptr(*buffer);
	get_line(line, s_text);
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	*s_text = NULL;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (read(fd, buffer, 0) < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (!s_text)
		s_text = ft_strdup("");
	if (read_file(fd, &buffer, &s_text, &line) == 0 && *line == '\0')
	{
		free_ptr(line);
		return (NULL);
	}
	return (line);
}

int main(int ac, char **av)
{
    int fd;
    (void)ac;
    (void)av;
	char *line;

    fd = open("klist.txt", O_RDONLY);
    if (fd == -1)
        return (printf("FD ERROR!"));    
    while ((line = get_next_line(fd)))
        printf("%s", line);
    
    return (0);
}
/*
	GET_NEXT_LINE
	-------------
	The function returns the next line from the fd with its respective '\n',
	or the last line of the file. It returns null if there's nothing to read
	or if an error occurs.
	AUXILIARY FUNCTIONS
	-------------------
	READ_FILE
	---------
	This function copies BUFFER_SIZE bytes from the string buffer to the
	static variable s_text until a newline is found or the end of file is
	reached.
	GET_LINE
	--------
	If a newline is found in the cumulative buffer s_text, the contents until
	'\n' are copied to line and the rest is stored again in s_text. If no
	newline is found, the whole content of s_text is copied to line and s_text
	points to NULL.
*/