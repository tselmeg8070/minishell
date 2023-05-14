/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_logic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 00:07:28 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/14 14:41:59 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_memory_error(int *res)
{
	write(2, "minishell: Error: Not enough memory available.\n", 47);
	*res = 1;
}

int	ft_command_parse(t_list	*command_table, t_env_list **env)
{
	int	res;

	res = 0;
	if (!ft_handle_instruction_redirection(command_table))
		ft_handle_memory_error(&res);
	if (res == 0 && !ft_handle_env_command(command_table, *env))
		ft_handle_memory_error(&res);
	if (res == 0 && !ft_handle_env_redirection(command_table, *env))
		ft_handle_memory_error(&res);
	if (res == 0 && !ft_generate_char_list_traverse(command_table))
		ft_handle_memory_error(&res);
	if (res == 0 && !ft_quote_strip_traverse(command_table))
		ft_handle_memory_error(&res);
	if (res == 0)
		res = ft_call_execution(command_table, env);
	ft_lstclear(&command_table, ft_free_instruction);
	return (res);
}

int	ft_lexa_parse(char *line, t_env_list **env)
{
	t_list	*list;
	t_list	*command_table;
	int		res;

	list = 0;
	res = 0;
	if (ft_tokenize(line, &list))
	{
		if (list && ft_token_check(list))
		{
			command_table = ft_token_seperation(list);
			if (command_table)
				res = ft_command_parse(command_table, env);
			else
				ft_handle_memory_error(&res);
		}
	}
	ft_lstclear(&list, free);
	ft_exit_status(res, env);
	unlink(".tmp");
	if (res == -1)
		ft_handle_memory_error(&res);
	return (res);
}
