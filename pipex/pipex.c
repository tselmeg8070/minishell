/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:18:41 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/01/31 17:18:42 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_get_fd(char *file, char *limit)
{
	char	*line;
	int		fd;

	line = "";
	if (ft_strncmp(file, "here_doc", ft_strlen(file)) == 0)
	{
		fd = open("tmp", O_RDWR | O_CREAT, 0666);
		while (line)
		{
			write(1, "heredoc>", 8);
			line = get_next_line(0);
			if (line && ft_strncmp(line, limit, ft_strlen(line) - 1) != 0)
				write(fd, line, ft_strlen(line));
			if (line && ft_strncmp(line, limit, ft_strlen(line) - 1) == 0)
			{
				free(line);
				close(fd);
				return (open("tmp", O_RDONLY));
			}
			free(line);
		}
		return (open("tmp", O_RDONLY));
	}
	return (open(file, O_RDONLY));
}

void	ft_handle_heredoc(char **argv, char **envp, int *res)
{
	int		link[2];
	int		fd;
	char	**paths;

	paths = ft_get_paths(envp);
	fd = ft_get_fd(argv[1], argv[2]);
	argv++;
	*res = ft_execute_loop(paths, argv, fd, link);
	ft_check_result_bonus(argv[ft_cnt_split(argv) - 1], link[0], res);
	ft_split_free(&paths);
	close(link[0]);
	close(fd);
	unlink("tmp");
}

int	main(int argc, char **argv, char **envp)
{
	int		link[2];
	int		fd;
	int		res;
	char	**paths;

	res = 1;
	if (argc == 5)
	{
		if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
			ft_handle_heredoc(argv, envp, &res);
		else
		{
			paths = ft_get_paths(envp);
			fd = ft_get_fd(argv[1], argv[2]);
			ft_in_check_access(argv[1]);
			res = ft_execute_loop(paths, argv, fd, link);
			ft_check_result(argv[ft_cnt_split(argv) - 1], link[0], &res);
			ft_split_free(&paths);
			close(link[0]);
			close(fd);
		}
	}
	if (res == 0)
		return (res);
	return (EXIT_FAILURE);
}
