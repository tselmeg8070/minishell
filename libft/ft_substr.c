/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 09:06:24 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/30 13:27:44 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	l;

	l = ft_strlen(s) - start;
	if (len < l)
		l = len;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	res = malloc(l + 1);
	if (res == 0)
		return (0);
	ft_strlcpy(res, (s + start), l + 1);
	return (res);
}
