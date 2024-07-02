/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishibas <rishibas@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:49:33 by rishibas          #+#    #+#             */
/*   Updated: 2024/07/02 17:40:35 by rishibas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*find_newline_into_line(char *read_part)
{
	int		i;
	char	*line;

	i = 0;
	while (read_part[i] != '\n' && read_part[i])
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
	{
		free(read_part);
		return (NULL);
	}
	i = 0;
	while (read_part[i] != '\n' && read_part[i])
	{
		line[i] = read_part[i];
		i++;
	}
	if (read_part[i] == '\n')
	{
		line[i] = read_part[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line_help(char *save, char *buf, int fd)
{
	ssize_t	n;
	char	*save_ptr;

	n = 1;
	while (!ft_strchr(save, '\n') && n != 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
			return (free(buf), NULL);
		buf[n] = '\0';
		if (!save)
			save = ft_strdup(buf);
		else
		{
			save_ptr = ft_strjoin(save, buf);
			if (!save_ptr)
				return (free(buf), free(save), NULL);
			free(save);
			save = save_ptr;
		}
	}
	free(buf);
	return (save);
}

char	*update_save(char *read_part, char *line)
{
	int		i;
	int		j;
	char	*save;

	i = 0;
	while (read_part[i] != '\n' && read_part[i])
		i++;
	if (!read_part[i])
		return (NULL);
	save = (char *)malloc(ft_strlen(read_part) - i + 1);
	if (!save)
	{
		line[0] = '\0';
		return (NULL);
	}
	j = 0;
	i++;
	while (read_part[i])
	{
		save[j] = read_part[i];
		i++;
		j++;
	}
	save[j] = '\0';
	return (save);
}

void	*ft_free(char **save, char *read_part, char *line)
{
	if (!*save)
	{
		free(line);
		free(read_part);
	}
	if (!read_part && *save)
	{
		free(*save);
		*save = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf;
	char		*line;
	char		*read_part;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	read_part = get_next_line_help(save, buf, fd);
	if (!read_part)
		return (ft_free(&save, read_part, 0));
	line = find_newline_into_line(read_part);
	if (!line)
		return (NULL);
	save = update_save(read_part, line);
	if (line[0] == '\0' && save == NULL)
		return (ft_free(&save, read_part, line));
	free(read_part);
	return (line);
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}

// // // // __attribute__((destructor))
// // // // static void destructor() {
// // // //     char command[256];
// // // //     snprintf(command, sizeof(command), "leaks -q %d", getpid());
// // // //     system(command);
// // // // }

int main(void)
{
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
        printf("%s", line);
		if (!line)
			return (0);
		free(line);
	}
	close(fd);
	return (0);
}
