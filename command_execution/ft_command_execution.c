/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:02:42 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/12 11:50:08 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_try_every_path(char **paths, char **arr, t_env_list **env)
{
	char	*str;
	char	*joined;
	char	**envs;
	int		i;

	i = 0;
	envs = ft_env_convert_original(*env);
	while (arr && paths[i])
	{
		str = ft_strjoin(paths[i], "/");
		joined = ft_strjoin(str, arr[0]);
		free(str);
		execve(joined, arr, envs);
		free(joined);
		i++;
	}
	execve(arr[0], arr, envs);
	ft_split_free(&envs);
}

int	ft_execute(char **paths, t_instruction *inst, t_env_list **env, int *link)
{
	int	perm_err;

	if (inst->redirection[0] >= 0)
	{
		if (inst->redirection[0] != 0)
			dup2(inst->redirection[0], STDIN_FILENO);
		if (inst->redirection[1] != 1)
			dup2(inst->redirection[1], STDOUT_FILENO);
		close(inst->pipe[0]);
		close(inst->pipe[1]);
		if (inst->in != 0)
			close(inst->in);
		if (inst->out != 1)
			close(inst->out);
		if (ft_builtin_check(inst->val))
			exit (ft_builtin_caller(inst->val, env));
		perm_err = ft_check_access(paths, inst->val[0]);
		if (perm_err == 1)
			ft_try_every_path(paths, inst->val, env);
		else
			exit (perm_err);
	}
	exit (EXIT_FAILURE);
}

static int	ft_execution_out_child(int pid, int *link, int *status)
{
	// waitpid(pid, status, 0);
	close(link[1]);
	return (link[0]);
}

static void	ft_handle_inputs(t_instruction *inst, t_list *cmd, int *link,
				int fd)
{
	if (inst->in == 0)
	{
		inst->in = fd;
	}
	if (cmd->next && inst->out == 1)
	{
		inst->out = link[1];
	}
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
	t_list			*cmd_table;

	status = 1;
	fd = 0;
	pid = 0;
	cmd_table = command_table;
	while (command_table)
	{
		inst = (t_instruction *) command_table->content;
		pipe(link);
		inst->pipe[0] = link[0];
		inst->pipe[1] = link[1];
		if (ft_command_redirection(inst) != -1 && inst->err_code == 0)
		{
			if (inst->in == 0)
				inst->redirection[0] = fd;
			else
				inst->redirection[0] = inst->in;
			if (command_table->next && inst->out == 1)
				inst->redirection[1] = link[1];
			else if (inst->out != 1)
				inst->redirection[1] = inst->out;
			pid = fork();
			if (pid == 0)
				return (ft_execute(paths, inst, env, link));
			else
			{
				inst->pid = pid;
				if (fd != 0)
					close(fd);
				close(inst->pipe[1]);
				if (inst->in != 0)
					close(inst->in);
				if (inst->out != 1)
					close(inst->out);
			}
		}
		else
			status = ft_handle_redirection_err(inst);
		fd = link[0];
		command_table = command_table->next;
	}
	while (cmd_table)
	{
		inst = (t_instruction *) cmd_table->content;
		if (inst->pid != 0 && inst->err_code == 0)
			waitpid(inst->pid, &status, 0);
		else
			status = inst->err_code;
		cmd_table = cmd_table->next;
	}
	if (fd != 0)
		close(fd);
	return (status % 255);
}
