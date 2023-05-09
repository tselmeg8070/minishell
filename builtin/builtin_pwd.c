/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galtange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:22:39 by galtange          #+#    #+#             */
/*   Updated: 2023/04/27 18:53:19 by galtange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (errno);
	}
	write (1, buffer, ft_strlen(buffer));
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
				write (1, "minishell: pwd: Permission denied", 34);
			else if (i == EFAULT)
				write (1, "minishell: pwd: Bad address", 28);
			else if (i == ENOENT)
				write (1, "minishell: pwd: No such file or directory", 42);
			write(1, "\n", 1);
			return (i);
		}
	}
	return (0);
}
