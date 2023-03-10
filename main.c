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
	cmd arg1 arg2 | cmd | cmd 'arg1' | cmd "fdsf" | cmd << end |
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
		if (quote == 0 && str[i] == '\'')
			quote = 1;
		else if (quote == 0 && str[i] == '\"')
			quote = 2;
		else if ((quote == 1 && str[i] == '\'')
			|| (quote == 2 && str[i] == '\"'))
			quote = 0;
		i++;
	}
	if (quote == 0)
		return (1);
	return (0);
}

int	ft_lexa_parse(char *str)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (quote == 0 && str[i] == '\'')
			quote = 1;
		else if (quote == 0 && str[i] == '\"')
			quote = 2;
		else if ((quote == 1 && str[i] == '\'')
			&& (quote == 2 && str[i] == '\"'))
			quote = 0;
		if (quote == 1)
			write(1, str + i, 1);
		i++;
	}
}

int	main(int argc, char **argv, char **paths)
{
	char	*line;

	while (1)
	{
		line = readline("minishell>");
		if (line)
		{
			if (ft_quote_check(line) == 0)
				write(2, "Unclosed quotation mark\n", 25);
			else
				printf("%s\n", line);
			free(line);
		}
	}
}
