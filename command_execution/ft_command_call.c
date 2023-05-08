/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_call.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:14:30 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/08 11:46:51 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_call_execution(t_list *command_table, t_env_list *env)
{
	char	*path;
	char	**paths;
	int		link[2];
	int		res;

	paths = 0;
	path = ft_find_elm(&env, "PATH");
	if (path)
		paths = ft_split(path, ':');
	res = ft_execute_loop(paths, command_table, link, env);
	close(link[0]);
	unlink("tmp");
	if (path)
		ft_split_free(&paths);
	return (res);
}