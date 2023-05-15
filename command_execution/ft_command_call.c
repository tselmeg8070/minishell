/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_call.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:14:30 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/15 21:47:14 by tadiyamu         ###   ########.fr       */
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
	int	res;
	t_instruction	*inst;
	int	in;
	int	out;

	res = -1;
	in = dup(0);
	out = dup(1);
	if (ft_lstlen(command_table) == 1)
	{
		inst = (t_instruction *) command_table->content;
		if (inst->val[0] && ft_builtin_check_parent(inst->val[0]))
		{
			if (ft_command_redirection(inst) != -1 && inst->err_code == 0)
			{
				if (inst->in != 0)
					dup2(inst->in, 0);
				if (inst->out != 0)
					dup2(inst->out, 1);
				if (ft_strcmp(inst->val[0], "exit") == 0)
					res = ((ft_exit_bt(inst->val) + 5) * -1);
				res = (ft_builtin_caller(inst->val, env));
				if (inst->in != 0)
				{
					close(inst->in);
					dup2(in, 0);
					close(in);
				}
				if (inst->out != 0)
				{
					close(inst->out);
					dup2(out, 1);
					close(out);
				}
			}
		}
	}
	return (res);
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
