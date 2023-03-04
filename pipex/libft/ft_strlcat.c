/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:25:53 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/28 15:14:04 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcat_strlen(char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
	{
		i++;
	}
	return (i);
}

unsigned int	ft_min(unsigned int a, unsigned int b)
{
	if (a > b)
		return (b);
	return (a);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	dest_l;
	unsigned int	src_l;
	unsigned int	i;

	if (dest == 0 && size == 0)
		return (0);
	dest_l = ft_strlcat_strlen(dest);
	src_l = ft_strlcat_strlen(src);
	if (size <= 0)
		return (ft_min(dest_l, size) + src_l);
	i = dest_l;
	while (i < size - 1 && src[i - dest_l] != '\0')
	{
		dest[i] = src[i - dest_l];
		i++;
	}
	dest[i] = '\0';
	return (ft_min(dest_l, size) + src_l);
}
