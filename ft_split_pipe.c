/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 20:35:27 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/16 19:20:49 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_split(char *str, char charset)
{
	int		i;
	int		str_flag;

	i = 0;
	str_flag = 0;
	while (*str != '\0')
	{
		if (*str == charset)
			str_flag = 0;
		else
		{
			if (!str_flag)
			{
				i++;
				str_flag = 1;
			}
		}
		str++;
	}
	return (i);
}

static char	**ft_malloc(int arr_c)
{
	char	**result;
	int		i;

	result = (char **) malloc(sizeof(char *) * (arr_c + 1));
	if (result == 0)
		return (0);
	i = 0;
	while (i < arr_c)
	{
		result[i] = 0;
		i++;
	}
	result[arr_c] = 0;
	return (result);
}

int	ft_check_quote(char const *strp, int index)
{
	char	*substr;
	int		res;

	substr = ft_substr(strp, 0, index);
	if (!substr)
		return (0);
	res = ft_quote_check(substr);
	free(substr);
	return (res);
}

char	**ft_split_pipe(char const *strp, char charset)
{
	int		c;
	char	**result;
	char	*str;
	char	*start;

	str = (char *) strp;
	c = ft_count_split(str, charset);
	result = ft_malloc(c);
	if (result == 0)
		return (0);
	c = 0;
	start = str;
	while (*str != '\0')
	{
		if (*str == charset && ft_check_quote(strp, str - strp))
		{
			if (*start != charset)
				result[c++] = ft_substr(start, 0, str - start);
			start = str + 1;
		}
		str++;
	}
	if (*start && *start != charset)
		result[c] = ft_substr(start, 0, str - start);
	return (result);
}
