/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:24:40 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/19 21:58:57 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_create_file(t_instruction *inst, t_redirection *red)
{
	int		out;

	out = open(red->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (inst->out != 1)
		close(inst->out);
	inst->out = out;
}

static void	ft_append_file(t_instruction *inst, t_redirection *red)
{
	int		out;

	out = open(red->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (inst->out != 1)
		close(inst->out);
	inst->out = out;
}

static void	ft_read_file(t_instruction *inst, t_redirection *red)
{
	int	fd;

	fd = open(red->filename, O_RDONLY);
	if (inst->in != 0)
		close(inst->in);
	inst->in = fd;
}

void	ft_redirection_file(t_instruction *inst, t_redirection *red)
{
	if (red->type == 2)
		ft_create_file(inst, red);
	else if (red->type == 4)
		ft_append_file(inst, red);
	else if (red->type == 3)
		ft_read_file(inst, red);
	else
		ft_here_doc(inst, red);
}
