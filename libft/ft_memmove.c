/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:25:57 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/28 14:42:30 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*ds;
	char	*sr;
	size_t	i;

	ds = (char *) dest;
	sr = (char *) src;
	if (ds == src)
		return (ds);
	while (ds > sr && n > 0)
	{
		ds[n - 1] = sr[n - 1];
		n--;
	}
	if (sr > ds)
	{
		i = 0;
		while (i < n)
		{
			ds[i] = sr[i];
			i++;
		}
	}
	return (dest);
}
