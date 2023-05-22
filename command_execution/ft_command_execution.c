/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:02:42 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/22 16:53:33 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	ft_execute_end_child(t_instruction *inst, int pid, int fd,
				int *red)
{
	dup2(red[0], 0);
	dup2(red[1], 1);
	close(inst->pipe[1]);
	if (inst->err_code == 0)
	{
		if (fd != 0 && fd >= 0)
			close(fd);
		inst->pid = pid;
		if (inst->in != 0 && inst->in >= 0)
			close(inst->in);
		if (inst->out != 1 && inst->out >= 0)
			close(inst->out);
	}
}

static void	ft_execute_loop_call_init(int *pid, int *fd, int *red)
{
	*pid = 0;
	*fd = 0;
	red[0] = dup(0);
	red[1] = dup(1);
}

static void	ft_execute_loop_call(char **paths, t_list *command_table,
				t_data **data, int *link)
{
	int				pid;
	t_instruction	*inst;
	int				fd;
	int				red[2];

	ft_execute_loop_call_init(&pid, &fd, red);
	while (command_table)
	{
		inst = (t_instruction *) command_table->content;
		pipe(link);
		ft_pipe_to_link(inst, link);
		if (ft_command_redirection(inst) != -1 && inst->err_code == 0)
		{
			ft_define_redirections(inst, command_table, fd);
			pid = fork();
			if (pid == 0)
				exit (ft_execute(paths, inst, data));
			else
				ft_execute_end_child(inst, pid, fd, red);
		}
		else
			ft_execute_end_child(inst, pid, fd, red);
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
	g_status[1] = 1;
	ft_execute_loop_call(paths, (*data)->command_table, data, link);
	ft_wait_execution((*data)->command_table, &status);
	if (status == 131)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	g_status[1] = 0;
	return (status % 255);
}
