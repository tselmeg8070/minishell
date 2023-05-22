/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:22:39 by galtange          #+#    #+#             */
/*   Updated: 2023/05/22 13:58:07 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_getcwd(int size)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * size);
	if (!buffer)
		return (1);
	if (getcwd(buffer, size) == NULL)
	{
		if (buffer)
			free(buffer);
		if (errno == ENOENT)
		{
			ft_putstr_fd("pwd: error retrieving current directory: ", 2);
			ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
			ft_putstr_fd("No such file or directory\n", 2);
		}
		return (errno);
	}
	write (1, buffer, ft_strlen(buffer));
	write (1, "\n", 1);
	free (buffer);
	return (0);
}

int	ft_pwd(char **strs)
{
	int	buff_size;
	int	i;

	(void) strs;
	buff_size = 42;
	i = 1;
	while (i > 0)
	{
		i = ft_getcwd(buff_size);
		if (i == ERANGE)
			buff_size++;
		else
		{
			if (i == EACCES)
				ft_putstr_fd("minishell: pwd: Permission denied\n", 2);
			else if (i == EFAULT)
				ft_putstr_fd ("minishell: pwd: Bad address\n", 2);
			return (1);
		}
	}
	return (0);
}
