/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galtange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:07:02 by galtange          #+#    #+#             */
/*   Updated: 2023/05/09 14:48:39 by galtange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
	}
	return (i);
}

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
		if (print_echo(*str) != 0 && (strs + 1) != NULL)
			write (1, " ", 1);
		strs++;
	}
	if (flag_n)
		write(1, "\n", 1);
	return (0);
}
