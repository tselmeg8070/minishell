/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 10:33:01 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/01/03 18:10:08 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *src, char *nl)
{
	size_t	s;
	size_t	i;
	char	*res;

	if (!src || !nl)
		return (0);
	res = 0;
	i = 0;
	s = nl - src;
	if (nl - src <= 0)
		return (0);
	res = (char *) malloc (s + 1);
	if (res == 0)
		return (0);
	while ((src + i) != nl)
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_prepare_line(char **res)
{
	char	*line;
	char	*nl;
	char	*dump;

	nl = ft_strchr(*res, '\n');
	line = ft_strdup(*res, nl + 1);
	if (!line)
		return (0);
	dump = ft_strdup(nl + 1, ft_strchr(*res, '\0'));
	free(*res);
	*res = dump;
	return (line);
}

int	get_next_line_buff(int fd, char **res)
{
	int		rc;
	char	*buff;
	char	*line;

	rc = 1;
	buff = malloc(BUFFER_SIZE + 1);
	while (fd >= 0 && !ft_strchr(*res, '\n') && rc > 0)
	{
		rc = read(fd, buff, BUFFER_SIZE);
		if (rc > 0)
		{
			line = *res;
			buff[rc] = '\0';
			*res = ft_strjoin(*res, buff);
			free(line);
		}
	}
	free(buff);
	return (rc);
}

char	*get_next_line(int fd)
{
	static char		*res = 0;
	char			*line;
	int				rc;

	line = 0;
	rc = get_next_line_buff(fd, &res);
	if (rc >= 0 && res && !ft_strchr(res, '\n'))
	{
		line = ft_strdup(res, ft_strchr(res, '\0'));
		free(res);
		res = 0;
		return (line);
	}
	if (rc >= 0 && res && ft_strchr(res, '\n'))
		line = ft_prepare_line(&res);
	return (line);
}
