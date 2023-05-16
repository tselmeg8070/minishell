/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:00:39 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/16 15:16:26 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_minishell_exit_result(int *res, t_data **data)
{
	*res = ft_lexa_parse(data);
	if (*res <= -5)
	{
		if ((*res + 5) * -1 != 257)
		{
			*res = (*res + 5) * -1 % 256;
			return (1);
		}
		else
		{
			*res = (*res + 5) * -1 % 256;
			ft_exit_status(*res, &(*data)->env);
		}
	}
	return (0);
}

void	ft_quotation_error(t_env_list **env)
{
	write(2, "Unclosed quotation mark\n", 25);
	ft_exit_status(1, env);
}

void	ft_init_env(t_data *data, char **paths)
{
	data->env = ft_create_envlist(paths);
	if (data->env == 0)
	{
		free(data);
		exit(ft_aff_msg(2, "Err\n", 1));
	}
}

void	ft_line_loop(int *res, t_data **data)
{
	while (1)
	{
		(*data)->line = readline("minishell>");
		if ((*data)->line)
		{
			if (ft_strlen((*data)->line) != 0 && !ft_only_spaces((*data)->line))
			{
				ft_history((*data)->line);
				if (ft_quote_check((*data)->line) == 0)
					ft_quotation_error(&(*data)->env);
				else if (ft_minishell_exit_result(res, data))
					break ;
			}
			free((*data)->line);
			(*data)->line = 0;
		}
		else
			break ;
	}
}

int	main(int argc, char **argv, char **paths)
{
	t_data				*data;
	struct sigaction	sa;
	int					res;

	res = 0;
	if (argc != 1 && argv[0])
		return (ft_aff_msg(2, "minishell: doesn't accept args\n", 1));
	data = ft_init_data();
	if (!data)
		return (ft_aff_msg(2, "minishell: not enough space to start\n", 1));
	ft_init_env(data, paths);
	ft_init_sig(&sa);
	ft_line_loop(&res, &data);
	rl_clear_history();
	ft_free_data(&data);
	return (res);
}
