/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_permission.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:02:56 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/22 17:11:04 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

int	ft_print_error(int err, char *name)
{
	if (err == 0)
	{
		write(2, "minishell: ", 12);
		write(2, name, ft_strlen(name));
		if (name[0] == '/' || ft_strncmp(name, "./", 2) == 0)
			write(2, " No such file or directory\n", 27);
		else
			write(2, " command not found\n", 19);
		return (127);
	}
	if (err == 2)
	{
		write(2, "minishell: is directrory: ", 26);
		write(2, name, ft_strlen(name));
		write(2, "\n", 1);
		return (126);
	}
	else if (err == 1 || name == 0)
	{
		write(2, "minishell: permission denied: ", 30);
		write(2, name, ft_strlen(name));
		write(2, "\n", 1);
		return (126);
	}
	return (1);
}

void	ft_check_access_helper(char *path, int *err)
{
	if (access(path, F_OK) == 0)
		*err = 1;
	if (access(path, X_OK) == 0)
		*err = 3;
	if (is_directory(path))
		*err = 2;
}

/*
Checks commands access
Return:
	(1) - No error
Fallback:
	(127) - command not found
	(126) - permission denied
*/
int	ft_check_access(char **paths, char *arr)
{
	int		i;
	char	*str;
	char	*path;
	int		err;

	err = 0;
	i = -1;
	if (arr && ft_strlen(arr) == 0)
		return (ft_print_error(0, arr));
	while (err != 3 && paths && paths[++i] && arr)
	{
		str = ft_strjoin(paths[i], "/");
		path = ft_strjoin(str, arr);
		free(str);
		ft_check_access_helper(path, &err);
		free(path);
	}
	if (arr && arr[0] == '/')
		ft_check_access_helper(arr, &err);
	if (arr && ft_strncmp(arr, "./", 2) == 0)
		ft_check_access_helper(arr, &err);
	err = ft_print_error(err, arr);
	if (err == 3)
		return (1);
	return (err);
}
