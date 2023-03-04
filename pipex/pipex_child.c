/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:50:46 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/02/06 17:50:48 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_try_every_path(char **paths, char *arr)
{
	char	*str;
	char	*joined;
	int		i;
	char	**arg;

	i = 0;
	arg = ft_split(arr, ' ');
	while (arg && paths[i])
	{
		str = ft_strjoin(paths[i], "/");
		joined = ft_strjoin(str, arg[0]);
		free(str);
		execve(joined, arg, (char **){NULL});
		free(joined);
		i++;
	}
	execve(arg[0], arg, (char **){NULL});
	ft_split_free(&arg);
}

int	ft_execute(char **paths, char *arr, int *link, int fd)
{
	if (fd >= 0)
	{
		dup2(fd, STDIN_FILENO);
		dup2(link[1], STDOUT_FILENO);
		close(link[0]);
		close(link[1]);
		close(fd);
		if (ft_check_access(paths, arr))
			ft_try_every_path(paths, arr);
	}
	close(link[0]);
	close(link[1]);
	return (EXIT_FAILURE);
}

int	ft_execute_loop(char **paths, char **argv, int fd, int *link)
{
	int		i;
	int		pid;
	int		status;

	i = 2;
	status = 1;
	while (i < ft_cnt_split(argv) - 1)
	{
		pipe(link);
		pid = fork();
		if (pid == 0)
			return (ft_execute(paths, argv[i], link, fd));
		waitpid(pid, &status, 0);
		close(link[1]);
		fd = link[0];
		i++;
	}
	return (status);
}
