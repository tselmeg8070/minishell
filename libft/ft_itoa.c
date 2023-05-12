/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 12:14:27 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/28 16:34:52 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_itoa_count_dig(int n)
{
	int	c;

	c = 0;
	if (n < 0)
		c++;
	while (n != 0)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

void	ft_itoa_rev(char *res, int s)
{
	int	i;
	int	temp;

	i = 0;
	while (s / 2 > i)
	{
		temp = res[i];
		res[i] = res[s - 1 - i];
		res[s - 1 - i] = temp;
		i++;
	}
}

char	*ft_itoa(int n)
{
	int		c;
	int		i;
	char	*res;

	if (n == 0)
		return (ft_strdup("0"));
	c = ft_itoa_count_dig(n);
	res = malloc(c + 1);
	if (res == 0)
		return (0);
	res[c] = 0;
	if (n < 0)
		res[c - 1] = '-';
	i = 0;
	while (n != 0)
	{
		if (n % 10 < 0)
			res[i++] = '0' + (n % 10) * (-1);
		else
			res[i++] = '0' + n % 10;
		n = n / 10;
	}
	ft_itoa_rev(res, c);
	return (res);
}
