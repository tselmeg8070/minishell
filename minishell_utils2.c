/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:00:39 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/03/04 17:00:42 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Concats char to string.
Edge case:
	memory fail
	res: *str = null;
*/
void	ft_concat_char(char **str, char c)
{
	char	*res;
	int		len;

	if (*str == 0)
		len = 0;
	else
		len = ft_strlen(*str);
	res = malloc(len + 2);
	if (res)
	{
		ft_memcpy(res, *str, len);
		res[len + 1] = '\0';
		res[len] = c;
	}
	free(*str);
	*str = res;
}

void	ft_concat_empty(char **val)
{
	*val = malloc(sizeof(char));
	if (*val)
		**val = '\0';
}

int	ft_concat_char_protected(char **token, char c)
{
	ft_concat_char(token, c);
	if (token == 0)
		return (0);
	return (1);
}

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
