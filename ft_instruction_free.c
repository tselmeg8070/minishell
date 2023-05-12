/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instruction_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:03:58 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/12 02:54:04 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_redirection(void *file)
{
	t_redirection	*redirection;

	redirection = (t_redirection *) file;
	free(redirection->filename);
	free(redirection->original);
	free(redirection);
}

void	ft_free_token(void *token)
{
	char	*string;

	string = (char *) token;
	if (token)
		free(string);
}

void	ft_free_instruction(void *rinst)
{
	t_instruction	*inst;

	inst = (t_instruction *) rinst;
	ft_lstclear(&inst->files, &ft_free_redirection);
	ft_lstclear(&inst->commands, &ft_free_token);
	ft_lstclear(&inst->tokens, &ft_free_token);
	ft_split_free(&inst->val);
	if (inst->err_msg)
		free(inst->err_msg);
	free(inst);
}
