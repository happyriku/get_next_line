#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *buf);
size_t	ft_strlen(const char *s);

#endif