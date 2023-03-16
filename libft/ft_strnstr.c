/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:32:48 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/28 15:16:20 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	search(char *str, char *to_find, size_t n)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && to_find[i] != '\0' && i < n)
	{
		if (str[i] != to_find[i])
			return (0);
		i++;
	}
	if (to_find[i] == '\0')
		return (1);
	return (0);
}

char	*ft_strnstr(const char *pstr, const char *pto_find, size_t n)
{
	size_t	i;
	char	*str;
	char	*to_find;

	str = (char *) pstr;
	to_find = (char *) pto_find;
	i = 0;
	if (str == 0 && n == 0)
		return (0);
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0' && i < n)
	{
		if (search(str + i, to_find, n - i))
			return (str + i);
		i++;
	}
	return (0);
}
