/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_execution_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:02:42 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/16 15:51:03 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handle_redirection_err(t_instruction *inst)
{
	close(inst->pipe[1]);
	if (inst->in != 0)
		close(inst->in);
	if (inst->out != 1)
		close(inst->out);
	write(2, "minishell: ", 11);
	write(2, inst->err_msg, ft_strlen(inst->err_msg));
	return (inst->err_code);
}

void	ft_try_every_path(char **paths, char **arr, t_env_list **env)
{
	char	*str;
	char	*joined;
	char	**envs;
	int		i;

	i = 0;
	envs = ft_env_convert_original(*env);
	while (arr && arr[0] && paths && paths[i])
	{
		str = ft_strjoin(paths[i], "/");
		joined = ft_strjoin(str, arr[0]);
		free(str);
		execve(joined, arr, envs);
		free(joined);
		i++;
	}
	if (arr && arr[0])
		execve(arr[0], arr, envs);
	ft_split_free(&envs);
}

int	ft_action(char **paths, t_instruction *inst, t_env_list **env)
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
			return (ft_builtin_caller(inst->val, env));
		perm_err = ft_check_access(paths, inst->val[0]);
		if (perm_err == 1)
			ft_try_every_path(paths, inst->val, env);
		else
			return (perm_err);
	}
	return (EXIT_FAILURE);
}

int	ft_execute(char **paths, t_instruction *inst, t_data **data)
{
	int	res;

	res = 0;
	if (inst->val && inst->val[0])
		res = ft_action(paths, inst, &(*data)->env);
	ft_free_data(data);
	ft_split_free(&paths);
	exit (res);
}


// static void	exec_child(int child, int *status, t_data *data)
// {
// 	struct sigaction	child_sigquit;

// 	ft_memset(&child_sigquit, 0, sizeof(struct sigaction));
// 	if (!child)
// 	{
// 		child_sigquit.sa_handler = &child_sigquit_handler;
// 		sigaction(SIGQUIT, &child_sigquit, NULL);
// 		close_redirection_fds(data);
// 		if (data->process[0].params)
// 		{
// 			if (execve(data->process[0].params[0],
// 					data->process[0].params, data->my_envp) == -1)
// 				error_fct(data, "minishell: Execve failure", 7);
// 		}
// 		free_data(data);
// 		exit(g_exit_status);
// 	}
// 	data->sigint.sa_handler = SIG_IGN;
// 	sigaction(SIGINT, &data->sigint, NULL);
// 	waitpid(child, status, 0);
// 	data->sigint.sa_handler = &main_sigint_handler;
// 	sigaction(SIGINT, &data->sigint, NULL);
// }


void	ft_wait_execution(t_list *cmd_table, int *status)
{
	t_instruction	*inst;

	while (cmd_table)
	{
		inst = (t_instruction *) cmd_table->content;
		if (inst->pid != 0 && inst->err_code == 0)
		{
			// struct sigaction sa_ch;
			// sa_ch.sa_handler = &child_handler;
			// sigaction(SIGINT, &sa_ch, NULL);
			waitpid(inst->pid, status, 0);
			// sa_ch.sa_handler = &parent_handler;
			// sigaction(SIGINT, &sa_ch, NULL);
		}
		else
			*status = ft_handle_redirection_err(inst);
		cmd_table = cmd_table->next;
	}
}
