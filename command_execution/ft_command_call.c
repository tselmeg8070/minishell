/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_call.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:14:30 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/15 20:56:21 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_builtin_check_parent(char *str)
{
	if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	return (0);
}

int	ft_call_single_builtin(t_list *command_table, t_env_list **env)
{
	t_instruction	*inst;

	if (ft_lstlen(command_table) == 1)
	{
		inst = (t_instruction *) command_table->content;
		if (inst->val[0] && ft_builtin_check_parent(inst->val[0]))
		{
			if (ft_strcmp(inst->val[0], "exit") == 0)
				return ((ft_exit_bt(inst->val) + 5) * -1);
			return (ft_builtin_caller(inst->val, env));
		}
	}
	return (-1);
}

int	ft_call_execution(t_data **data)
{
	char	*path;
	char	**paths;
	int		link[2];
	int		res;

	paths = 0;
	path = ft_find_elm(&(*data)->env, "PATH");
	if (path)
		paths = ft_split(path, ':');
	res = ft_call_single_builtin((*data)->command_table, &(*data)->env);
	if (res == -1)
	{
		res = ft_execute_loop(paths, data, link);
		close(link[0]);
	}
	if (path)
		ft_split_free(&paths);
	return (res);
}
