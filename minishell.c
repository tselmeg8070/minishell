/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:00:39 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/12 04:08:35 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_status = 0;

int	ft_minishell_exit_result(int *res, char *line, t_env_list **env)
{
	ft_exit_status(g_status, env);
	*res = ft_lexa_parse(line, env);
	if (*res <= -5)
	{
		if ((*res + 5) * -1 != 257)
		{
			*res = (*res + 5) * -1 % 256;
			free(line);
			return (1);
		}
		else
		{
			*res = (*res + 5) * -1 % 256;
			ft_exit_status(*res, env);
		}
	}
	return (0);
}

void	ft_quotation_error(t_env_list **env)
{
	write(2, "Unclosed quotation mark\n", 25);
	ft_exit_status(1, env);
}

void	ft_init_env(t_env_list **env, char **paths)
{
	*env = ft_create_envlist(paths);
	if (*env == 0)
		exit(ft_aff_msg(2, "Err\n", 1));
}

void	ft_line_loop(int *res, t_env_list **env)
{
	char	*line;

	while (1)
	{
		line = readline("minishell>");
		if (line)
		{
			if (ft_strlen(line) != 0)
			{
				ft_history(line);
				if (ft_quote_check(line) == 0)
					ft_quotation_error(env);
				else if (ft_minishell_exit_result(res, line, env))
					break ;
			}
			free(line);
		}
		else
			break ;
	}
}

int	main(int argc, char **argv, char **paths)
{
	t_env_list			*env;
	struct sigaction	sa;

	ft_init_env(&env, paths);
	ft_init_sig(&sa);
	if (argc != 1 && argv[0])
		return (ft_aff_msg(2, "Err: Minishell don't accept args\n", 1));
	ft_line_loop(&g_status, &env);
	rl_clear_history();
	ft_free_envlst(&env);
	return (g_status);
}
