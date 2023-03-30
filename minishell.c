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

void	ft_lexa_space(char *line)
{
	int		i;
	char	**strings;

	i = 0;
	strings = ft_split_pipe(line, ' ');
	while (strings[i])
	{
		printf("String: %s$\n", strings[i]);
		i++;
	}
	ft_split_free(&strings);
}

void	ft_instruction(char	*command, t_env_list *env)
{
	t_instruction	insts;
	char			*temp;

	insts.files = 0;
	insts.val = command;
	if (!ft_define_redirections(&insts, env))
		printf("Free the memory and return err\n");
	// temp = ft_replace_env(insts.val, env);
	// free(insts.val);
	// insts.val = temp;
	printf("Res: %s|\n", insts.val);
	free(insts.val);
}

void	ft_lexa_parse(char *line, t_env_list *env)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		ft_local_quoter(line[i], &quote);
		if (quote == 0)
		i++;
	}
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
		}
	}
	if (!ft_free_envlst(&env))
		printf ("list deleted!\n");
}
