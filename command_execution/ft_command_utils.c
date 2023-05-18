/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:35:50 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/18 22:43:03 by tadiyamu         ###   ########.fr       */
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
	close(out);
}

void	ft_pipe_to_link(t_instruction *inst, int *link)
{
	inst->pipe[0] = link[0];
	inst->pipe[1] = link[1];
}
