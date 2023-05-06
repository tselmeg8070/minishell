/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:04:15 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/06 19:04:16 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Creates token node
Fallback:
	(0/null) - Memory allocation fails
*/
t_list	*ft_create_token_node(t_list *token)
{
	t_list	*node;
	char	*token_val;

	token_val = strdup((char *) token->content);
	if (!token)
		return (0);
	node = ft_lstnew(token_val);
	if (!node)
		free(token_val);
	return (node);
}

/*
Creates and assigns tokens for instruction
Fallback:
	(0/null) - Memory allocation fails
*/
t_instruction	*ft_tokens_to_inst(t_list *start, t_list *end)
{
	t_instruction	*inst;
	t_list			*node;

	inst = ft_init_instruction();
	if (!inst)
		return (0);
	while (start != end)
	{
		if (strcmp(start->content, "|") != 0)
		{
			node = ft_create_token_node(start);
			if (!node)
			{
				ft_free_instruction(inst);
				return (0);
			}
			else
				ft_lstadd_back(&inst->tokens, node);
		}
		start = start->next;
	}
	return (inst);
}

/*
Seperates token to instructions
Fallback:
	(0/null) - memory allocation fails
*/
t_list	*ft_token_seperation(t_list *token)
{
	t_list			*insts;
	t_list			*next;
	t_list			*head;
	t_instruction	*inst;

	insts = 0;
	head = token;
	while (token)
	{
		next = token->next;
		if (strcmp(token->content, "|") == 0 || token->next == 0)
		{
			inst = ft_tokens_to_inst(head, token->next);
			if (inst && !ft_lstadd_back_safe(&insts, inst))
				return (0);
			head = token->next;
		}
		token = next;
	}
	return (insts);
}
