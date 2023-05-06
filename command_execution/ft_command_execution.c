/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:02:42 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/06 21:12:16 by tadiyamu         ###   ########.fr       */
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

int	ft_execute(char **paths, t_instruction *inst, int *link, int fd)
{
	if (fd >= 0)
	{
		if (inst->in != 0)
			fd = inst->in;
		dup2(fd, STDIN_FILENO);
		dup2(link[1], STDOUT_FILENO);
		close(link[0]);
		close(link[1]);
		close(fd);
		if (ft_check_access(paths, inst->val[0]))
			ft_try_every_path(paths, inst->val);
	}
	close(link[0]);
	close(link[1]);
	return (EXIT_FAILURE);
}

int	ft_execution_out_red(int out, int fd)
{
	if (out != 1)
	{
		ft_write_result(out, fd);
		return (0);
	}
	return (fd);
}

/*
Executes command table and creates/manages redirections
Return:
	(n) - 0 <= m < 256
Fallback:
	(-1) - memory error
*/
int	ft_execute_loop(char **paths, t_list *command_table, int fd, int *link)
{
	int				pid;
	int				status;
	t_instruction	*inst;

	status = 1;
	while (command_table)
	{
		inst = (t_instruction *) command_table->content;
		if (ft_command_redirection(inst) != -1 && inst->err_code == 0)
		{
			pipe(link);
			pid = fork();
			if (pid == 0)
				return (ft_execute(paths, inst, link, fd));
			waitpid(pid, &status, 0);
			close(link[1]);
			fd = ft_execution_out_red(inst->out, link[0]);
		}
		else
			printf("minishell: %s", inst->err_msg);
		command_table = command_table->next;
	}
	return (status);
}
