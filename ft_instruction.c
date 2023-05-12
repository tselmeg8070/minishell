/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instruction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:03:58 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/12 10:47:45 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Initializes the instruction
Fallback:
	(0/null) - Memory fails
*/
t_instruction	*ft_init_instruction(void)
{
	t_instruction	*inst;

	inst = malloc(sizeof(t_instruction));
	if (inst)
	{
		inst->pid = 0;
		inst->val = 0;
		inst->valc = 0;
		inst->in = 0;
		inst->out = 1;
		inst->pipe[0] = 0;
		inst->pipe[1] = 0;
		inst->redirection[0] = 0;
		inst->redirection[1] = 1;
		inst->err_msg = 0;
		inst->err_code = 0;
		inst->commands = 0;
		inst->files = 0;
		inst->tokens = 0;
	}
	return (inst);
}

t_list	*ft_init_instructions(void)
{
	t_list			*list;
	t_instruction	*inst;

	list = 0;
	inst = ft_init_instruction();
	if (inst)
	{
		list = ft_lstnew(inst);
		if (!list)
			free(inst);
		return (list);
	}
	return (0);
}

t_instruction	*ft_get_instuction(t_list *list)
{
	t_list			*node;
	t_instruction	*inst;

	node = ft_lstlast(list);
	inst = (t_instruction *) node->content;
	return (inst);
}

void	ft_add_instruction(t_list **list)
{
	t_list			*node;
	t_instruction	*inst;

	node = 0;
	inst = ft_init_instruction();
	if (inst)
		node = ft_lstnew(inst);
	if (node)
		ft_lstadd_back(list, node);
}
