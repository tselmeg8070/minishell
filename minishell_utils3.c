/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:00:39 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/11 17:11:00 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstlen(t_list *head)
{
	int	c;

	c = 0;
	while (head)
	{
		c++;
		head = head->next;
	}
	return (c);
}

void	ft_lstpop_front(t_list **list, void (*del)(void*))
{
	t_list	*next;
	t_list	*current;

	if (*list == 0)
		return ;
	current = *list;
	next = current->next;
	del(current->content);
	free(current);
	*list = next;
}

/*
Safely adds element to the list. If content is null its fallbacks.
Fallback:
	(0) - Memory fails and clears the current instruction list
*/
int	ft_lstadd_back_safe(t_list **list, void *content)
{
	t_list	*node;

	if (!content)
	{
		ft_lstclear(list, &ft_free_instruction);
		return (0);
	}
	node = ft_lstnew(content);
	if (!node)
	{
		ft_lstclear(list, &ft_free_instruction);
		return (0);
	}
	ft_lstadd_back(list, node);
	return (1);
}
