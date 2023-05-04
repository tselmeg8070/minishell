/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:00:39 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/03/04 17:00:42 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
PARSING:
	cmd arg1 arg2 | cmd | cmd 'arg1' | cmd "fdsf" |
	SPECIAL:
		" - Query string
		' - string
		> - redirect output
		< - redirect input file
		>> - redirect output using append
		<< - call heredoc with ending condition
		$ - call global variables or call command
		| - Pipe
		$? - exit status
		&& - AND operation
		|| - OR operation
		() - Prioritization
		* - Wildcard
**/

int	ft_quote_check(char *str)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		quote = ft_quoter(str[i], quote);
		i++;
	}
	if (quote == 0)
		return (1);
	return (0);
}

void	ft_check_list(void *file)
{
	char *temp = (char*) file;
	printf("CMD Token: %s\n", temp);
}

void	ft_check_redirections(void *file)
{
	t_redirection *temp = (t_redirection*) file;
	printf("Name: %s type: %d\n", temp->filename, temp->type);
}

void	ft_check_list_inst(void *file)
{
	t_instruction *temp = (t_instruction*) file;
	printf("Command:\n");
	ft_lstiter(temp->commands, ft_check_list);
	printf("Redirections:\n");
	ft_lstiter(temp->files, ft_check_redirections);
	printf("Expanded: \n");
	int i = 0;
	while (temp->val[i] != 0)
	{
		printf("Exp: %s\n", temp->val[i]);
		i++;
	}
}

void	ft_free_list_token(void *token)
{
	char *temp = (char*) token;
	free(temp);
}

void	ft_print_execution_res(int fd)
{
	char	*res;

	res = "";
	while (res)
	{
		res = get_next_line(fd);
		if (res)
		{
			printf("%s", res);
			free(res);
		}
	};
}

int		ft_call_execution(t_list *command_table, t_env_list *env)
{
	char	*path;
	char	**paths;
	int 	link[2];

	path = ft_find_elm(&env, "PATH");
	paths = ft_split(path, ':');
	ft_execute_loop(paths, command_table, 0, link);
	ft_print_execution_res(link[0]);
	close(link[0]);
	ft_split_free(&paths);
	return (1);
}

void	ft_lexa_parse(char *line, t_env_list *env)
{
	t_list	*list;
	t_list	*command_table;

	list = 0;
	if (ft_tokenize(line, &list))
	{
		if (ft_token_check(list))
		{
			command_table = ft_token_seperation(list);
			if (command_table)
			{
				ft_handle_instruction_redirection(command_table);
				ft_handle_env_command(command_table, env);
				ft_handle_env_redirection(command_table, env);
				ft_generate_char_list_traverse(command_table);
				ft_quote_strip_traverse(command_table);
				ft_call_execution(command_table, env);
				ft_lstclear(&command_table, ft_free_instruction);
			}
		}
	}
	ft_lstclear(&list, ft_free_list_token);
}

int	main(int argc, char **argv, char **paths)
{
	char		*line;
	t_env_list	*env;

	env = ft_create_envlist(paths);
	if (!env)
	{
		printf("err\n");
		return (0);
	}
	while (1)
	{
		line = readline("minishell>");
		if (line)
		{
			if (ft_quote_check(line) == 0)
				write(2, "Unclosed quotation mark\n", 25);
			else
			{
				ft_lexa_parse(line, env);
			}
			free(line);
		} else {
			ft_free_envlst(&env);
			return (0);
		}
	}
}
