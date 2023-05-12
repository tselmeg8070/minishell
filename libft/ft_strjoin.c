/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 09:27:16 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/27 20:26:42 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	res[i] = 0;
	return (res);
}
