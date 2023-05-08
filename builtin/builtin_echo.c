/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galtange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:07:02 by galtange          #+#    #+#             */
/*   Updated: 2023/05/08 17:28:18 by galtange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **strs)
{
	int		flag_n;

	if (!strs || !*strs)
	{
		write(1, "\n", 1);
		return (0);
	}
	flag_n = 1;
	if (*strs && !ft_strcmp(*strs, "-n"))
	{
		flag_n = 0;
		if (strs + 1)
			strs++;
	}
	while (*strs != NULL)
	{
		write (1, *strs, ft_strlen(*strs));
		strs++;
	}
	if (flag_n)
		printf("\n");
	return (0);
}
