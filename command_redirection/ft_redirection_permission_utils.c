/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_permission_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:24:54 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/18 16:43:55 by tadiyamu         ###   ########.fr       */
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
int	ft_gen_error_msg(t_instruction *inst, char *name, int id)
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
