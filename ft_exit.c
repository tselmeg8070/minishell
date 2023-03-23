/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galtange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:30:04 by galtange          #+#    #+#             */
/*   Updated: 2023/03/19 21:47:34 by galtange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char *line, t_env_list **env)
{
	if (line)
		free(line);
	if (env)
		ft_free_envlst(env);
	rl_clear_history ();
	write (1, "exit\n", 5);
	return (EOF);
}

void	ft_history(char *line)
{
	if (line && ft_strncmp(line, "", 1))
		add_history (line);
	rl_redisplay ();
}

// void	ft_exit2(int status)
// {
// 	if (status == 127)
// 		printf("Command 'duudagdsan command' not found, did you mean:\n");
// 	if (status)
// 	{

// 	}
// }

void	exit_from_child(int	status, char *bltin, char *cmd, char *msg)
{
	printf("status = %d\n", status);
	if (bltin)
		printf("%s: ", bltin);
	if (cmd)
		printf("`%s': ", cmd);
	if (msg)
		printf("%s\n", msg);
	return ;
}