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

int	ft_flag_n(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] != '\0' && str[i] == 'n')
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

int	ft_echo(char **strs)
{
	int	flag_n;

	if (strs && !ft_strcmp(*strs, "echo"))
		strs++;
	flag_n = 1;
	while (*strs)
	{
		if (ft_flag_n(*strs))
			flag_n = 0;
		else
			break ;
		strs++;
	}
	if (*strs)
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
