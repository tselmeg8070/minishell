/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:32:22 by galtange          #+#    #+#             */
/*   Updated: 2023/05/07 23:46:40 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_handler(int sig)
{
	ft_putnbr_fd(g_status, 1);
	if (g_status == 1)
	{
		ft_putstr_fd("here\n", 1);
		// g_status = sig + 128;
		signal(sig, SIG_IGN);
		exit(sig + 128);
	}
	else
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_history("");
		g_status = sig + 128;
	}
}

void	child_handler(int sig)
{
	// if (sig == SIGINT)
	// 	signal(SIGINT, SIG_IGN);
	exit(sig + 128);
}

void	ft_init_sig(struct sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = SA_RESTART;
	sa->sa_handler = &parent_handler;
	if (sigaction(SIGINT, sa, NULL) == -1)
	{
		ft_putstr_fd("Sigaction error!\n", 2);
		exit(1);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
