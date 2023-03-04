/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:18:41 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/02/05 16:42:53 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_paths(char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	path = 0;
	paths = 0;
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i];
		i++;
	}
	if (path)
	{
		path = ft_strchr(path, '=');
		path++;
		paths = ft_split(path, ':');
	}
	return (paths);
}

int	ft_cnt_split(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i] != 0)
		i++;
	return (i);
}

void	ft_split_free(char ***res)
{
	int	i;

	i = 0;
	while ((*res) && (*res)[i] != 0)
	{
		free((*res)[i]);
		i++;
	}
	if (*res)
		free(*res);
}

void	ft_command_free(char ***res, char **joined)
{
	ft_split_free(res);
	free(*joined);
}
