/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:03:47 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/06 19:03:48 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_red_token_id(t_list *token)
{
	if (token == 0)
		return (0);
	if (ft_strcmp(">>", (char *) token->content) == 0)
		return (4);
	if (ft_strcmp("<<", (char *) token->content) == 0)
		return (5);
	if (ft_strcmp(">", (char *) token->content) == 0)
		return (2);
	if (ft_strcmp("<", (char *) token->content) == 0)
		return (3);
	return (0);
}

int	ft_red_filename_free(t_redirection *red)
{
	free(red->filename);
	free(red);
	return (0);
}

/*
Assign filename to structure and adds it to list
Fallback:
	(0) - memory fail
*/
int	ft_red_filename(char *str, int type, t_list **list)
{
	int				i;
	t_redirection	*redirection;
	t_list			*node;

	redirection = malloc(sizeof(t_redirection));
	if (!redirection)
		return (0);
	redirection->filename = ft_strdup(str);
	if (!redirection->filename)
	{
		free(redirection);
		return (0);
	}
	redirection->type = type;
	node = ft_lstnew(redirection);
	if (node)
		ft_lstadd_back(list, node);
	else
		return (ft_red_filename_free(redirection));
	return (1);
}

/*
Assigns redirections to instruction files
Fallback:
	(0) - memory fail(handle free in parent function)
*/
int	ft_handle_redirection_command(t_instruction *inst)
{
	t_list	*token;
	t_list	*pre;
	int		red_id;

	token = inst->tokens;
	pre = 0;
	while (token)
	{
		red_id = ft_red_token_id(pre);
		if (pre && ft_red_token_id(pre) != 0
			&& !ft_red_filename(token->content, red_id, &inst->files))
			return (0);
		else if ((!pre || (pre && ft_red_token_id(pre) == 0))
			&& ft_red_token_id(token) == 0)
		{
			if (!ft_lstadd_back_safe(&inst->commands, ft_strdup(token->content)))
				return (0);
		}
		pre = token;
		token = token->next;
	}
	return (1);
}

/*
Redirection parser from instruction
Fallback:
	(0) - memory error
*/
int	ft_handle_instruction_redirection(t_list *inst)
{
	while (inst)
	{
		if (!ft_handle_redirection_command(inst->content))
			return (0);
		inst = inst->next;
	}
	return (1);
}
