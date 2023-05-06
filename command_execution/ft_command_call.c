/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_call.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:14:30 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/06 20:21:04 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_execution_res(int fd)
{
	char	*res;

	res = "";
	while (res)
	{
		res = get_next_line(fd);
		if (res)
		{
			printf("%s", res);
			free(res);
		}
	};
}

int		ft_call_execution(t_list *command_table, t_env_list *env)
{
	char	*path;
	char	**paths;
	int 	link[2];
	int		res;

	paths = 0;
	path = ft_find_elm(&env, "PATH");
	if (path)
		paths = ft_split(path, ':');
	res = ft_execute_loop(paths, command_table, 0, link);
	ft_print_execution_res(link[0]);
	close(link[0]);
	if (path)
		ft_split_free(&paths);
	return (res);
}
