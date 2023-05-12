/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_execution_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:02:42 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/12 10:52:24 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handle_redirection_err(t_instruction *inst)
{
	close(inst->pipe[1]);
	if (inst->in != 0)
		close(inst->in);
	if (inst->out != 1)
		close(inst->out);
	write(2, "minishell: ", 11);
	write(2, inst->err_msg, ft_strlen(inst->err_msg));
	return (inst->err_code);
}
