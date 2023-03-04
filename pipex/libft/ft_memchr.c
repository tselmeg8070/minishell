/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:09:17 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/29 18:17:10 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t	i;
	char	*cpy;

	cpy = (char *) str;
	i = 0;
	while (i < n)
	{
		if (cpy[i] == (c % 256))
			return (cpy + i);
		i++;
	}
	return (0);
}
