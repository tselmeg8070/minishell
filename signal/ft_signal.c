/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:32:22 by galtange          #+#    #+#             */
/*   Updated: 2023/05/18 22:16:21 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status[0] = 130;
		if (g_status[1] == 0)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			write(1, "\n", 1);
		}
	}
}

void	ft_init_sig(struct sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = SA_RESTART;
	sa->sa_handler = handler;
	if (sigaction(SIGINT, sa, NULL) == -1)
	{
		ft_putstr_fd("Sigaction error!\n", 2);
		exit(1);
	}
	signal(SIGQUIT, SIG_IGN);
	if (g_status[1] != 0)
		ft_putstr_fd("test\n", 1);
}

void	ft_sigquit_handler(int sig)
{
	write(2, "Quit (core dumped)\n", 20);
	g_status[0] = sig + 130;
}
