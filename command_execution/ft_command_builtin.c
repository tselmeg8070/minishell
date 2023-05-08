/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:35:13 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/08 18:50:00 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Built in caller
Return:
	(0 <= n <= 255) - builtin command result
Fallback:
	(-1) - if command is not built in
*/
int	ft_builtin_caller(char **vals, t_env_list **env_list)
{
	if (ft_strcmp(vals[0], "builtin") == 0)
	{
		write(1, "Calling builtin\n", 17);
		return (0);
	}
	// if (ft_strcmp(args[0], "export") == 0)
	// 	return (ft_export_test(args, env_list));
	// else if (ft_strcmp(args[0], "exit") == 0)
	// 	return (ft_export_test(args, env_list));
	// else if (ft_strcmp(args[0], "echo") == 0)
	// 	return (ft_export_test(args, env_list));
	// else if (ft_strcmp(args[0], "cd") == 0)
	// 	return (ft_export_test(args, env_list));
	// else if (ft_strcmp(args[0], "pwd") == 0)
	// 	return (ft_export_test(args, env_list));
	// else if (ft_strcmp(args[0], "unset") == 0)
	// 	return (ft_export_test(args, env_list));
	// else if (ft_strcmp(args[0], "env") == 0)
	// 	return (ft_export_test(args, env_list));
	// else
		return (-1);
}
