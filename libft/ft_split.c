/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 20:35:27 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/29 13:01:38 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_splt(char *str, char charset)
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

char	**ft_mallc(int arr_c)
{
	char	**result;

	result = (char **) malloc(sizeof(char *) * (arr_c + 1));
	if (result == 0)
		return (0);
	result[arr_c] = 0;
	return (result);
}

char	**ft_split(char const *strp, char charset)
{
	int		c;
	char	**result;
	char	*str;
	char	*start;

	str = (char *) strp;
	c = ft_count_splt(str, charset);
	result = ft_mallc(c);
	if (result == 0)
		return (0);
	c = 0;
	start = str;
	while (*str != '\0')
	{
		if (*str == charset)
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