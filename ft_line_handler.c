/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:47:33 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/18 15:58:24 by tadiyamu         ###   ########.fr       */
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

static int	ft_check_pipe(char *line)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			if (line[i] == '|' && c == 1)
				return (0);
			if (line[i] == '|')
				c = 1;
			else
				c = 0;
		}
		i++;
	}
	return (c);
}

static int	ft_check_start_pipe(char *line)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			if (line[i] == '|' && c == 0)
				return (1);
			else
				c++;
		}
		i++;
	}
	return (0);
}

int	ft_ensure_pipe_close(t_data **data)
{
	char	*line;
	char	*temp;

	while (ft_check_pipe((*data)->line))
	{
		line = readline(">");
		if (line)
		{
			if (ft_strlen((*data)->line) != 0 && !ft_only_spaces((*data)->line))
			{
				temp = (*data)->line;
				(*data)->line = ft_strjoin((*data)->line, line);
				free(temp);
				if ((*data)->line == 0)
					ft_ensure_pipe_mem_error(data);
			}
			free(line);
		}
		else
			ft_ensure_pipe_error(data);
	}
	return (1);
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
				if (ft_check_start_pipe((*data)->line))
					ft_start_pipe_error(data);
				else
				{
					ft_history((*data)->line);
					if (ft_quote_check((*data)->line) == 0)
						ft_quotation_error(&(*data)->env);
					else if (ft_minishell_exit_result(res, data))
						break ;
				}
			}
			free((*data)->line);
			(*data)->line = 0;
		}
		else
			break ;
	}
}
