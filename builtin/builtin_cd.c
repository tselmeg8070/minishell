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

int	ft_count_strs(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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

int	ft_change_dir(char *str)
{
	int	i;

	i = chdir(str);
	if (i)
	{
		ft_chdir_errmsg(str, errno);
		return (1);
	}
	return (0);
}

int	ft_cd(char **str)
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
		path = ft_strdup(getenv("HOME"));
	else if (!ft_strcmp(*str, "-"))
		path = ft_strdup(getenv("OLDPWD"));
	else
		path = ft_strdup(*str);
	if (!path)
		return (1);
	i = ft_change_dir(path);
	free (path);
	return (i);
}

	// ft_putstr_fd(path, 1);
	// write(1, "\n", 1);

	// else if (i == 0 || !ft_strcmp(*str, "~"))
	// {
	// 	ft_putstr_fd("chdir to home\n", 1);
	// 	path = ft_strdup(getenv("HOME"));
	// }
