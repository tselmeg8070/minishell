/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_loop.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:24:49 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/19 23:30:25 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Strips quotation mark from redirection's filename
Fallback:
	(-1) - memory fails
*/
int	ft_redirection_strip_quotation(t_redirection *red)
{
	char	*temp;

	temp = ft_strip(red->filename);
	if (!temp)
		return (-1);
	free(red->filename);
	red->filename = temp;
	return (0);
}

/*
Redirection handler for per instruction
Fallback:
	(-1) - Memory fails
*/
int	ft_command_redirection(t_instruction *inst)
{
	t_list			*files;
	t_redirection	*red;
	int				res;

	files = inst->files;
	while (files && inst->err_code == 0)
	{
		red = (t_redirection *) files->content;
		res = ft_check_ambiguous(inst, red);
		if (res != 0)
			return (res);
		res = ft_redirection_strip_quotation(red);
		if (res != 0)
			return (res);
		res = ft_check_red_permission(inst, red);
		if (res != 0)
			return (res);
		ft_redirection_file(inst, red);
		files = files->next;
	}
	return (0);
}
