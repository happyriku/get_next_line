/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rishibas <rishibas@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:15:20 by rishibas          #+#    #+#             */
/*   Updated: 2024/05/21 18:12:10 by rishibas         ###   ########.fr       */
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

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;
    int     s1_size;

	if (s1 == NULL)
		s1_size = 0;
	else
		s1_size = ft_strlen(s1);
	dest = (char *)malloc((s1_size + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < s1_size)
	{
		dest[i] = s1[i];
		i++;
	}
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
    free(s1);
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