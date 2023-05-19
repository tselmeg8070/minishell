/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:32:22 by galtange          #+#    #+#             */
/*   Updated: 2023/05/19 21:20:01 by tadiyamu         ###   ########.fr       */
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
		else if (g_status[1] == 1)
			write(1, "\n", 1);
		else if (g_status[1] == 2)
		{
			g_status[1] = 0;
			write(1, "\n", 1);
			close(0);
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
}

void	ft_sig_from_child(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(131);
}
