/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:09:30 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/11 21:22:16 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_all_digits(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if (!ft_isdigit(str[i][j]))
			{
				write(2, "minishell: exit: ", 18);
				ft_putstr_fd(str[i], 2);
				write(2, ": numeric argument required\n", 29);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

//exit: bash: exit: too many arguments - dont exit
int	ft_exit_bt(char	**str)
{
	int	exit_val;

	if (!str || !*str)
		return (1);
	if (str && !ft_strcmp(*str, "exit"))
		str++;
	if (!*str)
	{
		write (1, "exit\n", 5);
		return (0);
	}
	else if (str && ft_count_strs(str) > 1)
	{
		write (1, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	else if (str && !ft_all_digits(str))
		return (2);
	else if (str && ft_all_digits(str) == 1)
		exit_val = ft_atoi(*str) % 256;
	return (exit_val);
}

// int	ft_exit_bt(char **str)
// {
// 	int	exit_val;

// 	write(2, "exit\n", 5);
// 	if (str && !ft_all_digits(str))
// 		return (2);
// 	else if (str && ft_count_strs(str) > 1)
// 	{
// 		write(2, "minishell: exit: too many arguments\n", 37);
// 		return (1);
// 	}
// 	else if (!str || !*str)
// 	{
// 		return (0);
// 	}
// 	else
// 		exit_val = ft_atoi(*str) % 256;
// 	return (exit_val);
// }
