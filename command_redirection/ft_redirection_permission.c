/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_permission.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:24:54 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/17 19:39:23 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Generates error message and assigns that into instruction data structure
Return:
	(0) - id matches to error
	(1) - no error
Fallback:
	(-1) - memory fails
*/
static int	ft_gen_error_msg(t_instruction *inst, char *name, int id)
{
	if (id != 0)
	{
		inst->err_code = 1;
		if (id == 1)
			inst->err_msg = ft_strjoin(name, ": No such file or directory\n");
		if (id == 2)
			inst->err_msg = ft_strjoin(name, ": Permission denied\n");
		if (id == 3)
			inst->err_msg = ft_strjoin(name, ": Is a directory\n");
		if (!inst->err_msg)
			return (-1);
		return (1);
	}
	return (0);
}

/*
Checks write permission of the file
Result:
	(0) - file not found
	(1) - is directory
*/
static int	ft_is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

static int	ft_check_has_dir(char *path)
{
	char	**paths;
	int		i;
	int		c;

	i = 0;
	c = 0;
	paths = ft_split(path, '/');
	while (paths && paths[i])
	{
		if (ft_strcmp(paths[i], ".") != 0 || ft_strcmp(paths[i], "..") != 0)
			c++;
		i++;
	}
	if (paths)
		ft_split_free(&paths);
	if (c == 1)
		return (0);
	return (1);
}

/*
Checks write permission of the file
Result:
	(0) - has all necessary permissions
	(1) - don't have write permission
*/
static int	ft_check_write_access(char *path)
{
	if ((access(path, F_OK) == 0 && access(path, W_OK) != 0))
		return (1);
	if ((access(path, F_OK) != 0 && ft_check_has_dir(path)))
		return (3);
	return (0);
}

/*
Checks read permission of the file
Result:
	(0) - has all necessary permissions to read
	(1) - file not found
	(2) - don't have read permission
*/
static int	ft_check_read_access(char *path)
{
	if (access(path, F_OK) != 0)
		return (1);
	else if (access(path, R_OK) != 0)
		return (2);
	return (0);
}

/*
Checks necessary permissions for given redirection.
Result:
	(0) - has all necessary permissions
	(1) - permission error
Fallback:
	(-1) - memory fail
*/
int	ft_check_red_permission(t_instruction *inst, t_redirection *red)
{
	int	read;

	if (red->type != 5 && ft_is_directory(red->filename))
		return (ft_gen_error_msg(inst, red->filename, 3));
	if ((red->type == 2 || red->type == 4))
	{
		read = ft_check_write_access(red->filename);
		if (read == 1)
			return (ft_gen_error_msg(inst, red->filename, 2));
		else if (read == 3)
			return (ft_gen_error_msg(inst, red->filename, 1));
	}
	if (red->type == 3)
	{
		read = ft_check_read_access(red->filename);
		ft_gen_error_msg(inst, red->filename, read);
		if (read == 0)
			return (0);
		return (1);
	}
	return (0);
}
