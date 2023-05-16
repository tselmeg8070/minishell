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

void	handler(int sig)
{
	(void) sig;
	if (getpid() == 0)
	{
		write(1, "test", 4);
		exit (130);
	}
	else
	{
		write(2, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_putnbr_fd(g_status, 1);
		g_status = 130;
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
}

void	ft_sigint_child(int sig)
{
	signal(sig, SIG_IGN);
	exit(130);
}