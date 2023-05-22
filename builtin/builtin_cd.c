/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:29:55 by galtange          #+#    #+#             */
/*   Updated: 2023/05/22 13:57:42 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_chdir_errmsg(char *str, int errn)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
		write(2, ": ", 2);
	}
	if (errn == 13)
		ft_putstr_fd("Permission denied", 2);
	else if (errn == 14)
		ft_putstr_fd("Bad address", 2);
	else if (errn == 5)
		ft_putstr_fd("Input/output error", 2);
	else if (errn == 40)
		ft_putstr_fd("Too many levels of symbolic links", 2);
	else if (errn == 36)
		ft_putstr_fd("File name too long", 2);
	else if (errn == 12)
		ft_putstr_fd("Cannot allocate memory", 2);
	else if (errn == 20)
		ft_putstr_fd("Not a directory", 2);
	else
		ft_putstr_fd("No such file or directory", 2);
	printf("\n");
}

int	ft_change_dir(char *str, t_env_list **envs)
{
	int	i;

	if (ft_strcmp(str, ""))
	{
		i = chdir(str);
		if (i)
		{
			ft_chdir_errmsg(str, errno);
			return (1);
		}
	}
	ft_set_pwds(envs);
	return (0);
}

char	*ft_get_path(char *str, int argc, t_env_list **envs)
{
	char	*path;

	if (argc == 0)
	{
		path = ft_find_elm(envs, "HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else if (!ft_strcmp(str, "~"))
		path = getenv("HOME");
	else if (!ft_strcmp(str, "-"))
	{
		path = ft_find_elm(envs, "OLDPWD");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
	}
	else
		path = str;
	return (path);
}

int	ft_cd(char **str, t_env_list **envs)
{
	int		i;
	char	*path;

	if (!str || !*str)
		return (1);
	if (!ft_strcmp(*str, "cd"))
		str++;
	i = ft_count_strs(str);
	if (i > 1)
		return (ft_aff_msg(2, "minishell: cd: too many arguments\n", 1));
	path = ft_get_path(*str, i, envs);
	if (!path)
		return (1);
	i = ft_change_dir(path, envs);
	return (i);
}
