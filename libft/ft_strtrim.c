/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:27:08 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/28 18:03:18 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	setf(char const *set, size_t size, char c)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim_res(char const *s1, size_t start, size_t end)
{
	size_t	i;
	char	*res;

	res = 0;
	if (end - start + 2 > 0)
		res = malloc(end - start + 2);
	if (res == 0)
		return (0);
	i = 0;
	while (start <= end)
	{
		res[i] = s1[start];
		i++;
		start++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_size;
	size_t	set_size;
	size_t	start;
	size_t	end;

	s1_size = ft_strlen(s1);
	set_size = ft_strlen(set);
	start = 0;
	while (start < s1_size && setf(set, set_size, s1[start]))
		start++;
	if (start >= s1_size)
		return (ft_strdup(""));
	end = s1_size - 1;
	while (end != 0 && setf(set, set_size, s1[end]))
		end--;
	return (ft_strtrim_res(s1, start, end));
}
