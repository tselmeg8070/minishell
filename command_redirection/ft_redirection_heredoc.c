/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:51:00 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/19 23:09:41 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_here_doc_init(t_instruction *inst, int *fd)
{
	if (inst->in != 0)
		close(inst->in);
	g_status[1] = 2;
	*fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (dup(0));
}

static void	ft_here_doc_close(t_instruction *inst, int in, int fd)
{
	if (g_status[1] != 2)
		inst->err_code = 130;
	dup2(in, 0);
	close(in);
	g_status[1] = 0;
	close(fd);
	inst->in = open(".tmp", O_RDONLY);
}

void	ft_here_doc(t_instruction *inst, t_redirection *red)
{
	int		fd;
	char	*line;
	int		in;

	in = ft_here_doc_init(inst, &fd);
	while (g_status[1] == 2)
	{
		line = readline("> ");
		if (line)
		{
			if (ft_strcmp(line, red->filename) == 0)
			{
				free(line);
				break ;
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		else
			break ;
	}
	ft_here_doc_close(inst, in, fd);
}
