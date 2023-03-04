/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:18:41 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/02/06 18:30:28 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_print_error(int err, char *name)
{
	if (err == 0)
	{
		write(2, "pipex: command not found: ", 26);
		write(2, name, ft_strlen(name));
		write(2, "\n", 1);
	}
	else if (err == 1 || name == 0)
	{
		write(2, "pipex: permission denied: ", 26);
		write(2, name, ft_strlen(name));
		write(2, "\n", 1);
	}
}

int	ft_check_access(char **paths, char *arr)
{
	int		i;
	char	*str;
	char	*path;
	char	**args;
	int		err;

	err = 0;
	i = 0;
	args = ft_split(arr, ' ');
	while (args && paths[i++] && args[0])
	{
		str = ft_strjoin(paths[i], "/");
		path = ft_strjoin(str, args[0]);
		free(str);
		if (access(path, F_OK) == 0)
			err = 1;
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			err = 2;
		free(path);
	}
	ft_print_error(err, args[0]);
	ft_split_free(&args);
	if (err == 2)
		return (1);
	return (0);
}

int	ft_in_check_access(char *path)
{
	if (access(path, F_OK) != 0)
	{
		write(2, "pipex: No such file or directory: ", 34);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		return (0);
	}
	else
	{
		if (access(path, R_OK) != 0)
		{
			write(2, "pipex: permission denied: ", 26);
			write(2, path, ft_strlen(path));
			write(2, "\n", 1);
			return (0);
		}
	}
	return (1);
}

int	ft_check_result(char *path, int fd, int *res)
{
	char	*line;
	int		out;

	if ((access(path, F_OK) == 0 && access(path, W_OK) != 0))
	{
		*res = 1;
		write(2, "pipex: permission denied: ", 26);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		return (0);
	}
	unlink(path);
	line = "";
	out = open(path, O_WRONLY | O_CREAT, 0644);
	while (line != 0)
	{
		line = get_next_line(fd);
		if (line)
		{
			write(out, line, ft_strlen(line));
			free(line);
		}
	}
	close(out);
	return (0);
}

int	ft_check_result_bonus(char *path, int fd, int *res)
{
	char	*line;
	int		out;

	if ((access(path, F_OK) == 0 && access(path, W_OK) != 0))
	{
		*res = 1;
		write(2, "pipex: permission denied: ", 26);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		return (0);
	}
	line = "";
	out = open(path, O_WRONLY | O_APPEND, 0644);
	while (line != 0)
	{
		line = get_next_line(fd);
		if (line)
		{
			write(out, line, ft_strlen(line));
			free(line);
		}
	}
	close(out);
	return (0);
}
