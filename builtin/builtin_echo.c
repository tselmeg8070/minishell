/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:07:02 by galtange          #+#    #+#             */
/*   Updated: 2023/05/09 14:55:45 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int	flag_n;

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
	if (strs != NULL)
		print_echo(*strs++);
	while (*strs)
	{
		write (1, " ", 1);
		print_echo(*strs);
		strs++;
	}
	if (flag_n != 0)
		write(1, "\n", 1);
	return (0);
}
