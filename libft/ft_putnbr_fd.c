/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:51:37 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/27 23:51:32 by tg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd_count(int n)
{
	int	c;

	c = 0;
	while (n != 0)
	{
		c++;
		n = n / 10;
	}
	return (c);
}

void	ft_putnbr_fd_gen(int *pow)
{
	int	i;
	int	val;

	val = 1;
	i = 0;
	while (i < 10)
	{
		pow[i] = val;
		val *= 10;
		i++;
	}
}

int	ft_putnbr_fd_abs(int n)
{
	if (n < 0)
		return ((-1) * n);
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		pow[10];
	int		c;
	int		val;

	ft_putnbr_fd_gen(pow);
	c = ft_putnbr_fd_count(n) - 1;
	if (n == 0)
		ft_putchar_fd('0', fd);
	if (n < 0)
		ft_putchar_fd('-', fd);
	while (c >= 0)
	{
		val = n / pow[c];
		ft_putchar_fd(ft_putnbr_fd_abs(val) + '0', fd);
		n = n - val * pow[c];
		c--;
	}
}
