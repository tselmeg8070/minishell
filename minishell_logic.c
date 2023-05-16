/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_logic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 00:07:28 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/15 19:57:14 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_memory_error(int *res)
{
	write(2, "minishell: Error: Not enough memory available.\n", 47);
	*res = 1;
}

int	ft_command_parse(t_data **data)
{
	int	res;

	res = 0;
	if (!ft_handle_instruction_redirection((*data)->command_table))
		ft_handle_memory_error(&res);
	if (res == 0
		&& !ft_handle_env_command((*data)->command_table, (*data)->env))
		ft_handle_memory_error(&res);
	if (res == 0
		&& !ft_handle_env_redirection((*data)->command_table, (*data)->env))
		ft_handle_memory_error(&res);
	if (res == 0 && !ft_generate_char_list_traverse((*data)->command_table))
		ft_handle_memory_error(&res);
	if (res == 0 && !ft_quote_strip_traverse((*data)->command_table))
		ft_handle_memory_error(&res);
	if (res == 0)
		res = ft_call_execution(data);
	ft_lstclear(&(*data)->command_table, ft_free_instruction);
	return (res);
}

int	ft_lexa_parse(t_data **data)
{
	int		res;

	res = 0;
	if (ft_tokenize((*data)->line, &(*data)->tokens))
	{
		if ((*data)->tokens && ft_token_check((*data)->tokens))
		{
			(*data)->command_table = ft_token_seperation((*data)->tokens);
			if ((*data)->command_table)
				res = ft_command_parse(data);
			else
				ft_handle_memory_error(&res);
		}
	}
	ft_lstclear(&(*data)->tokens, free);
	ft_exit_status(res, &(*data)->env);
	unlink(".tmp");
	if (res == -1)
		ft_handle_memory_error(&res);
	return (res);
}
