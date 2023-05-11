/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:00:39 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/11 20:32:52 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Concats char to string.
Edge case:
	memory fail
	res: *str = null;
*/
void	ft_concat_char(char **str, char c)
{
	char	*res;
	int		len;

	if (*str == 0)
		len = 0;
	else
		len = ft_strlen(*str);
	res = malloc(len + 2);
	if (res)
	{
		ft_memcpy(res, *str, len);
		res[len + 1] = '\0';
		res[len] = c;
	}
	free(*str);
	*str = res;
}

void	ft_concat_empty(char **val)
{
	*val = malloc(sizeof(char));
	if (*val)
		**val = '\0';
}

int	ft_concat_char_protected(char **token, char c)
{
	ft_concat_char(token, c);
	if (token == 0)
		return (0);
	return (1);
}
