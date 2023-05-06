/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_permission.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:02:56 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/06 19:02:57 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_error(int err, char *name)
{
	if (err == 0)
	{
		write(2, "minishell: command not found: ", 30);
		write(2, name, ft_strlen(name));
		write(2, "\n", 1);
	}
	else if (err == 1 || name == 0)
	{
		write(2, "minishell: permission denied: ", 30);
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
