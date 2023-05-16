/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_handler_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:47:33 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/16 18:05:52 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quotation_error(t_env_list **env)
{
	write(2, "Unclosed quotation mark\n", 25);
	ft_exit_status(1, env);
}

void	ft_ensure_pipe_error(t_data **data)
{
	ft_free_data(data);
	write(2, "minishell: syntax error: unexpected end of file\n", 49);
	write(2, "exit\n", 5);
	exit (2);
}

void	ft_ensure_pipe_mem_error(t_data **data)
{
	ft_free_data(data);
	write(2, "minishell: mem error\n", 22);
	write(2, "exit\n", 5);
	exit (1);
}
