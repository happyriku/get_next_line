/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishibas <rishibas@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:15:20 by rishibas          #+#    #+#             */
/*   Updated: 2024/05/20 20:58:32 by rishibas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *buf)
{
	char	*dest;
	int		size;
	int		i;

	if (buf == NULL)
		return (NULL);
	i = -1;
	size = ft_strlen(buf) + 1;
	dest = (char *)malloc(size * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (++i < size)
		dest[i] = buf[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;
    size_t  len_s1;
    size_t  len_s2;

    if (s1 == NULL)
        len_s1 = 0;
    else
        len_s1 = ft_strlen(s1);
    if (s2 == NULL)
        len_s2 = 0;
    else
        len_s2 = ft_strlen(s2);
	str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
    if (s1 != NULL)
    {
	    while (s1[i])
        {
		    str[i] = s1[i];
            i++;
        }
    }
	j = 0;
    if (s2 != NULL)
    {
	    while (s2[j])
	    {
		    str[i] = s2[j];
		    i++;
		    j++;
	    }
    }
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	char	a;

	a = c;
	while (*s != a)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}