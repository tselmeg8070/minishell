/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:37:53 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/29 18:20:13 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*temp;

	temp = (char *) str;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == (c % 256))
			return (temp + i);
		i++;
	}
	if ((c % 256) == 0)
		return (temp + i);
	return (0);
}
