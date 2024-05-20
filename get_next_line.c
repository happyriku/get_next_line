/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishibas <rishibas@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:49:33 by rishibas          #+#    #+#             */
/*   Updated: 2024/05/20 21:00:24 by rishibas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*find_newline_return_line(char *read_part)
{
	int 	i;
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

char	*get_next_line_help(char *memo, char *buf, int fd)
{
	ssize_t	n;
	char	*temp;
	char	*add;
	char	*new_buf;

	add = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!add)
		return (NULL);
	n = read(fd, buf, BUFFER_SIZE);
	buf[n] = '\0';
	while (!ft_strchr(buf, '\n') && n != 0)
	{
		n = read(fd, add, BUFFER_SIZE);
		if (n < 0)
		{
			if (memo)
			{
				free(memo);
				memo = NULL;
			}
			free(buf);
			free(add);
			return (NULL);
		}
		add[n] = '\0';
		new_buf = ft_strjoin(buf, add);
		free(buf);
		// free(add);
		buf = new_buf;
	}
	free(add);
	if (n > 0)
	{
		if (!memo)
			memo = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(memo, buf);
			free(memo);
			memo = temp;
		}
	}
	if (n == 0)
	{
		temp = ft_strjoin(memo, buf);
		free(memo);
		memo = temp;
	}
	free(buf);
	return (memo);
}

char	*update_memo(char *read_part)
{
	int		i;
	int		j;
	char	*memo;

	i = 0;
	while (read_part[i] != '\n' && read_part[i])
		i++;
	if (!read_part[i])
		return (NULL);
	memo = (char *)malloc(ft_strlen(read_part) - i + 1);
	if (!memo)
		return (NULL);
	j = 0;
    i++;
	while (read_part[i])
	{
		memo[j] = read_part[i];
		i++;
		j++;
	}
	memo[j] = '\0';
	return (memo);
}

char	*get_next_line(int fd)
{
	static char *memo;
	char		*buf;
	char		*line;
	char		*read_part;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	read_part = get_next_line_help(memo, buf, fd);
	if (!read_part)
		return (NULL);
	line = find_newline_return_line(read_part);
	if (!line)
	{
		if (memo)
			free(memo);
		return (NULL);
	}
	memo = update_memo(read_part);
	if (line[0] == '\0' && memo == NULL)
		return (NULL);
	free(read_part);
	return (line);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }

__attribute__((destructor))
static void destructor() {
    char command[256];
    snprintf(command, sizeof(command), "leaks -q %d", getpid());
    system(command);
}

int main(void)
{
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}