/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_permission.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:24:54 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/06 19:26:01 by tadiyamu         ###   ########.fr       */
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
		if (!inst->err_msg)
			return (-1);
		return (0);
	}
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

	if ((red->type == 2 || red->type == 4)
		&& ft_check_write_access(red->filename))
		return (ft_gen_error_msg(inst, red->filename, 2));
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
