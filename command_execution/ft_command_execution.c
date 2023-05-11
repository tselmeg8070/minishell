/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:02:42 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/11 21:28:14 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_try_every_path(char **paths, char **arr)
{
	char	*str;
	char	*joined;
	int		i;

	i = 0;
	while (arr && paths[i])
	{
		str = ft_strjoin(paths[i], "/");
		joined = ft_strjoin(str, arr[0]);
		free(str);
		execve(joined, arr, (char **){NULL});
		free(joined);
		i++;
	}
	execve(arr[0], arr, (char **){NULL});
}

int	ft_execute(char **paths, t_instruction *inst, t_env_list **env, int *link)
{
	int	perm_err;

	close(link[0]);
	if (inst->in >= 0)
	{
		if (inst->in != 0)
		{
			dup2(inst->in, STDIN_FILENO);
			close(inst->in);
		}
		if (inst->out != 1)
		{
			dup2(inst->out, STDOUT_FILENO);
			close(inst->out);
		}
		if (ft_builtin_check(inst->val))
			exit (ft_builtin_caller(inst->val, env));
		perm_err = ft_check_access(paths, inst->val[0]);
		if (perm_err == 1)
			ft_try_every_path(paths, inst->val);
		else
			exit (perm_err);
	}
	exit (EXIT_FAILURE);
}

static int	ft_execution_out_child(int pid, int *link, int *status)
{
	waitpid(pid, status, 0);
	close(link[1]);
	return (link[0]);
}

static void	ft_handle_inputs(t_instruction *inst, t_list *cmd, int *link,
				int fd)
{
	if (inst->in == 0)
		inst->in = fd;
	if (cmd->next && inst->out == 1)
		inst->out = link[1];
}

/*
Executes command table and creates/manages redirections
Return:
	(n) - 0 <= m < 256
Fallback:
	(-1) - memory error
*/
int	ft_execute_loop(char **paths, t_list *command_table, int *link,
		t_env_list **env)
{
	int				pid;
	int				status;
	t_instruction	*inst;
	int				fd;

	status = 1;
	fd = 0;
	while (command_table)
	{
		inst = (t_instruction *) command_table->content;
		pipe(link);
		if (ft_command_redirection(inst) != -1 && inst->err_code == 0)
		{
			ft_handle_inputs(inst, command_table, link, fd);
			pid = fork();
			if (pid == 0)
				return (ft_execute(paths, inst, env, link));
			else
				fd = ft_execution_out_child(pid, link, &status);
		}
		else
			fd = ft_handle_redirection_err(inst, link);
		command_table = command_table->next;
	}
	return (status % 255);
}
