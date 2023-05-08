/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:00:39 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/08 00:38:31 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_memory_error(int *res)
{
	write(2, "minishell: Error: Not enough memory available.", 46);
	*res = 1;
}

int	ft_command_parse(t_list	*command_table, t_env_list *env)
{
	int	res;

	res = 0;
	if (!ft_handle_instruction_redirection(command_table))
		ft_handle_memory_error(&res);
	if (res == 0 && !ft_handle_env_command(command_table, env))
		ft_handle_memory_error(&res);
	if (res == 0 && !ft_handle_env_redirection(command_table, env))
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

int	ft_lexa_parse(char *line, t_env_list *env)
{
	t_list	*list;
	t_list	*command_table;
	int		res;

	list = 0;
	res = 0;
	if (ft_tokenize(line, &list))
	{
		if (ft_token_check(list))
		{
			command_table = ft_token_seperation(list);
			if (command_table)
				res = ft_command_parse(command_table, env);
			else
				ft_handle_memory_error(&res);
		}
	}
	ft_lstclear(&list, free);
	if (res == -1)
		ft_handle_memory_error(&res);
	return (res);
}

void	ft_history(char *line)
{
	if (line && ft_strncmp(line, "", 1))
		add_history(line);
	rl_redisplay();
}

int	main(int argc, char **argv, char **paths)
{
	char				*line;
	t_env_list			*env;
	struct sigaction	sa;

	env = ft_create_envlist(paths);
	if (!env)
	{
		printf("err\n");
		return (1);
	}
	ft_init_sig(&sa);
	while (1)
	{
		line = readline("minishell>");
		if (line)
		{
			ft_history(line);
			if (ft_quote_check(line) == 0)
				write(2, "Unclosed quotation mark\n", 25);
			else
				ft_lexa_parse(line, env);
			free(line);
		}
		else
		{
			rl_clear_history();
			ft_free_envlst(&env);
			return (0);
		}
	}
}
