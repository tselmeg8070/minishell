/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:29:55 by galtange          #+#    #+#             */
/*   Updated: 2023/05/09 22:00:04 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_chdir_errmsg(char *str, int errn)
{
	ft_putstr_fd("minishell> cd: ", 2);
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
	else if (errn == 2)
		ft_putstr_fd("No such file or directory", 2);
	printf("\n");
}

int	ft_set_oldpwd(t_env_list **envs)
{
	t_env_list	*tmp;
	char		*old_pwd;

	old_pwd = ft_find_elm(envs, "PWD");
	if (!old_pwd)
		return (1);
	tmp = *envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			free(tmp->val);
			tmp->val = ft_strdup(old_pwd);
			if (!tmp->val)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_set_newpwd(t_env_list **envs)
{
	int			buff_size;
	char		*buffer;
	t_env_list	*tmp;

	buff_size = 4096;
	buffer = malloc(sizeof(char) * buff_size);
	if (!buffer)
		return (1);
	if (getcwd(buffer, buff_size) == NULL)
		return (1);
	tmp = *envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			free(tmp->val);
			tmp->val = ft_strdup(buffer);
			if (!tmp->val)
				return (1);
		}
		tmp = tmp->next;
	}
	free (buffer);
	return (0);
}

int	ft_change_dir(char *str, t_env_list **envs)
{
	int	i;

	(void) envs;
	i = chdir(str);
	if (i)
	{
		ft_chdir_errmsg(str, errno);
		return (1);
	}
	if (ft_set_oldpwd(envs))
		return (1);
	if (ft_set_newpwd(envs))
		return (1);
	return (0);
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
	path = NULL;
	if (i > 1)
	{
		ft_putstr_fd("minishell> cd: too many arguments\n", 2);
		return (1);
	}
	else if (i == 0 || !ft_strcmp(*str, "~"))
		path = ft_strdup(ft_find_elm(envs, "HOME"));
	else if (!ft_strcmp(*str, "-"))
		path = ft_strdup(ft_find_elm(envs, "OLDPWD"));
	else
		path = ft_strdup(*str);
	if (!path)
		return (1);
	i = ft_change_dir(path, envs);
	free (path);
	return (i);
}
