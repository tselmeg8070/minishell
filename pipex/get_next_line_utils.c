/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:39:22 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/01/02 17:52:42 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	c;

	if (str == 0)
		return (0);
	c = 0;
	while (str[c] != '\0')
		c++;
	return (c);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1_size;
	size_t	s2_size;
	size_t	i;

	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	res = malloc(s1_size + s2_size + 1);
	if (res == 0)
		return (0);
	i = 0;
	while (i < s1_size)
	{
		res[i] = s1[i];
		i++;
	}
	while (i < s1_size + s2_size)
	{
		res[i] = s2[i - s1_size];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*temp;

	temp = (char *) str;
	if (str == 0)
		return (0);
	i = 0;
	while (str && str[i] != 0)
	{
		if (str[i] == (c % 256))
			return (temp + i);
		i++;
	}
	if ((c % 256) == 0)
		return (temp + i);
	return (0);
}
