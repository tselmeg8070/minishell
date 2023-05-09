/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:02:42 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/09 14:53:26 by tadiyamu         ###   ########.fr       */
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

int	ft_builtin_echo(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

int	ft_execute(char **paths, t_instruction *inst, t_env_list **env)
{
	int	perm_err;

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
			return (ft_builtin_caller(inst->val, env));
		perm_err = ft_check_access(paths, inst->val[0]);
		if (perm_err == 1)
			ft_try_every_path(paths, inst->val);
		else
			return (perm_err);
	}
	return (EXIT_FAILURE);
}

static int	ft_execution_out_child(int pid, int *link, int *status)
{
	waitpid(pid, status, 0);
	close(link[1]);
	return (link[0]);
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
			if (inst->in == 0)
				inst->in = fd;
			if (command_table->next && inst->out == 1)
				inst->out = link[1];
			pid = fork();
			if (pid == 0)
			{
				close(link[0]);
				status = (ft_execute(paths, inst, env));
				exit(status);
			}
			else
			{
				waitpid(pid, &status, 0);
				close(link[1]);
				fd = (link[0]);
			}
		}
		else
			printf("minishell: %s", inst->err_msg);
		command_table = command_table->next;
	}
	return (status);
}
