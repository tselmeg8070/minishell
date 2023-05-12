/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:08:05 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/27 23:31:14 by tg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int		l;
	unsigned int		i;

	l = ft_strlen(s);
	i = 0;
	while (i < l)
	{
		f(i, (s + i));
		i++;
	}
}
