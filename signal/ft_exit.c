/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galtange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:30:04 by galtange          #+#    #+#             */
/*   Updated: 2023/05/04 15:57:48 by galtange         ###   ########.fr       */
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
	if (line && ft_strcmp(line, ""))
		add_history (line);
	rl_redisplay ();
}

int	ft_aff_msg(int fd, char *str, int exit_val)
{
	if (fd < 0)
		return (1);
	if (str)
		ft_putstr_fd(str, fd);
	return (exit_val);
}

// void	exit_from_child(int status, char *bltin, char *cmd, char *msg)
// {
// 	printf("status = %d\n", status);
// 	if (bltin)
// 		printf("%s: ", bltin);
// 	if (cmd)
// 		printf("`%s': ", cmd);
// 	if (msg)
// 		printf("%s\n", msg);
// 	return ;
// }
