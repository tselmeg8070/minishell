/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:37:53 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/29 18:22:03 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*temp;
	char	*res;

	res = 0;
	temp = (char *) str;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == (c % 256))
			res = temp + i;
		i++;
	}
	if ((c % 256) == 0)
		return (temp + i);
	return (res);
}
