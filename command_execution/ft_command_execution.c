/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:02:42 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/15 20:21:24 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_wait_execution(t_list *cmd_table, int *status)
{
	t_instruction	*inst;

	while (cmd_table)
	{
		inst = (t_instruction *) cmd_table->content;
		if (inst->pid != 0 && inst->err_code == 0)
			waitpid(inst->pid, status, 0);
		else
			*status = ft_handle_redirection_err(inst);
		cmd_table = cmd_table->next;
	}
}

static void	ft_define_redirections(t_instruction *inst, t_list *command_table,
				int fd)
{
	if (inst->in == 0)
		inst->redirection[0] = fd;
	else
		inst->redirection[0] = inst->in;
	if (command_table->next && inst->out == 1)
		inst->redirection[1] = inst->pipe[1];
	else if (inst->out != 1)
		inst->redirection[1] = inst->out;
}

static void	ft_execute_end_child(t_instruction *inst, int pid, int fd)
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

static void	ft_execute_loop_call(char **paths, t_list *command_table,
				t_data **data, int *link)
{
	int				pid;
	t_instruction	*inst;
	int				fd;

	pid = 0;
	fd = 0;
	while (command_table)
	{
		inst = (t_instruction *) command_table->content;
		pipe(link);
		inst->pipe[0] = link[0];
		inst->pipe[1] = link[1];
		if (ft_command_redirection(inst) != -1 && inst->err_code == 0)
		{
			ft_define_redirections(inst, command_table, fd);
			pid = fork();
			if (pid == 0)
				exit (ft_execute(paths, inst, data, link));
			else
				ft_execute_end_child(inst, pid, fd);
		}
		fd = link[0];
		command_table = command_table->next;
	}
}

/*
Executes command table and creates/manages redirections
Return:
	(n) - 0 <= m < 256
Fallback:
	(-1) - memory error
*/
int	ft_execute_loop(char **paths, t_data **data, int *link)
{
	int				status;

	status = 1;
	ft_execute_loop_call(paths, (*data)->command_table, data, link);
	ft_wait_execution((*data)->command_table, &status);
	return (status % 255);
}
