/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:33:31 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/29 18:48:10 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	size_t	i;
	char	*res;

	i = 0;
	if (n > 9223372036854775807 || size > 9223372036854775807)
		return (NULL);
	res = malloc(n * size);
	if (res)
	{
		while (i < n * size)
		{
			*(res + i) = 0;
			i++;
		}
	}
	return (res);
}
