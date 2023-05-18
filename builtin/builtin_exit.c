/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:09:30 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/12 00:57:12 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_all_digits(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
		{
			write(2, "minishell: exit: ", 18);
			ft_putstr_fd(str, 2);
			write(2, ": numeric argument required\n", 29);
			return (0);
		}
		i++;
	}
	return (1);
}

unsigned long long	ft_long_atoi(char *str)
{
	unsigned long long	nb;

	if (!str)
		return (1);
	nb = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
			nb = nb * 10 + (*str - '0');
		str++;
	}
	return (nb);
}

int	ft_exit_calc(char *str)
{
	unsigned long long	val;
	long long			return_val;

	if (!str)
		return (1);
	if (!ft_strcmp(str, "-9223372036854775808"))
		val = 0;
	else
		val = ft_long_atoi(str);
	if (9223372036854775807 < val)
	{
		write(2, "minishell: exit: ", 18);
		ft_putstr_fd(str, 2);
		write(2, ": numeric argument required\n", 29);
		return (2 + 256);
	}
	return_val = 1;
	if (*str == '-')
		return_val = -1;
	return_val = (val * return_val) % 256;
	return (return_val + 256);
}

int	ft_exit_bt(char **str)
{
	if (!str || !*str)
		return (1);
	if (str && !ft_strcmp(*str, "exit"))
		str++;
	write (1, "exit\n", 5);
	if (!*str)
		return (0 + 256);
	if (str && ft_count_strs(str) == 1)
	{
		if (!ft_all_digits(*str))
			return (2 + 256);
		else
			return (ft_exit_calc(*str));
	}
	else
	{
		if (!ft_all_digits(*str))
			return (2 + 256);
		else
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			return (1 + 256);
		}
	}
	return (0);
}
