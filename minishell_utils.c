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

void	ft_split_free(char ***res)
{
	int	i;

	i = 0;
	while ((*res) && (*res)[i] != 0)
	{
		free((*res)[i]);
		i++;
	}
	if (*res)
		free(*res);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_quoter(char c, int quote)
{
	if (quote == 0 && c == '\'')
		quote = 1;
	else if (quote == 0 && c == '\"')
		quote = 2;
	else if ((quote == 1 && c == '\'') || (quote == 2 && c == '\"'))
		quote = 0;
	return (quote);
}

int	ft_local_quoter(char c, int *quote)
{
	if (*quote == 0 && c == '\'')
	{
		*quote = 1;
		return (1);
	}
	else if (*quote == 0 && c == '\"')
	{
		*quote = 2;
		return (1);
	}
	else if ((*quote == 1 && c == '\'') || (*quote == 2 && c == '\"'))
	{
		*quote = 0;
		return (1);
	}
	return (0);
}
