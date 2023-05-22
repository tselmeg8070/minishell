/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:00:39 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/22 15:54:41 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status[2];

void	ft_init_env(t_data *data, char **paths)
{
	data->env = ft_create_envlist(paths);
	if (data->env == 0)
	{
		free(data);
		exit(ft_aff_msg(2, "Err\n", 1));
	}
}

int	main(int argc, char **argv, char **paths)
{
	t_data				*data;
	struct sigaction	sa;
	int					res;

	res = 0;
	g_status[0] = 0;
	g_status[1] = 0;
	if (argc != 1 && argv[0])
		return (ft_aff_msg(2, "minishell: doesn't accept args\n", 1));
	data = ft_init_data();
	if (!data)
		return (ft_aff_msg(2, "minishell: not enough space to start\n", 1));
	ft_init_env(data, paths);
	ft_init_sig(&sa);
	ft_line_loop(&res, &data);
	rl_clear_history();
	ft_free_data(&data);
	return (g_status[0]);
}
