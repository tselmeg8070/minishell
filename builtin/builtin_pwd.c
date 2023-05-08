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
		return (-1);
	if (getcwd(buffer, size) == NULL)
	{
		if (buffer)
			free(buffer);
		if (errno == ERANGE)
			return (0);
		else if (errno == EACCES)
			return (-2);
		else if (errno == EFAULT)
			return (-3);
		else if (errno == ENOENT)
			return (-4);
	}
	printf("%s\n", buffer);
	free (buffer);
	return (1);
}

void	ft_pwd(char **strs)
{
	int	buff_size;
	int	i;

	(void) strs;
	buff_size = 42;
	i = 0;
	while (i <= 0)
	{
		i = ft_getcwd(buff_size);
		if (i == 0)
			buff_size++;
		else if (i < 0)
		{
			if (i == -2)
				printf("Permission to read\n");
			else if (i == -3)
				printf("buf points to a bad address\n");
			else if (i == -4)
				printf("The current working directory has been unlinked\n");
			break ;
		}
	}
}
