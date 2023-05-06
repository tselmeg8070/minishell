/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:35:50 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/06 20:35:52 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_write_result(int out, int fd)
{
	char	*line;

	line = "";
	while (line != 0)
	{
		line = get_next_line(fd);
		if (line)
		{
			write(out, line, ft_strlen(line));
			free(line);
		}
	}
	close(fd);
	close(out);
}
