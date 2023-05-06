/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:24:40 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/06 19:25:34 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_create_file(t_instruction *inst, t_redirection *red)
{
	int		out;

	out = open(red->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (inst->out != 1)
		close(inst->out);
	inst->out = out;
}

static void	ft_append_file(t_instruction *inst, t_redirection *red)
{
	int		out;

	out = open(red->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (inst->out != 1)
		close(inst->out);
	inst->out = out;
}

static void	ft_read_file(t_instruction *inst, t_redirection *red)
{
	int	fd;

	fd = open(red->filename, O_RDONLY);
	if (inst->in != 0)
		close(inst->in);
	inst->in = fd;
}

static void	ft_here_doc(t_instruction *inst, t_redirection *red)
{
	int		fd;
	char	*line;

	line = "";
	fd = open("tmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	while (line)
	{
		write(1, ">", 1);
		line = get_next_line(0);
		if (line && ft_strncmp(line, red->filename, ft_strlen(line) - 1) != 0)
			write(fd, line, ft_strlen(line));
		if (line && ft_strncmp(line, red->filename, ft_strlen(line) - 1) == 0)
		{
			free(line);
			close(fd);
			break ;
		}
		free(line);
	}
	fd = open("tmp", O_RDONLY);
	if (inst->in != 0)
		close(inst->in);
	inst->in = fd;
}

void	ft_redirection_file(t_instruction *inst, t_redirection *red)
{
	if (red->type == 2)
		ft_create_file(inst, red);
	else if (red->type == 4)
		ft_append_file(inst, red);
	else if (red->type == 3)
		ft_read_file(inst, red);
	else
		ft_here_doc(inst, red);
}
