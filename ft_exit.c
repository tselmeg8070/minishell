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
