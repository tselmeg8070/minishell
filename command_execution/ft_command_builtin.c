/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:35:13 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/11 22:06:53 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Check if command is built-in or not
Result:
	(1) - Yep
	(0) - No
*/
int	ft_builtin_check(char **args)
{
	if (ft_strcmp(args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(args[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(args[0], "env") == 0)
		return (1);
	else
		return (0);
}

/*
Built in caller
Return:
	(0 <= n <= 255) - builtin command result
Fallback:
	(-1) - if command is not built in
*/
int	ft_builtin_caller(char **args, t_env_list **env_list)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args, env_list));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit_bt(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(args));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args, env_list));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(env_list));
	else
		return (-1);
}
