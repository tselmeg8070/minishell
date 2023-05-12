/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:23:26 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/30 13:47:34 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_create_elem(void *data)
{
	t_list		*temp;

	temp = malloc(sizeof(t_list));
	if (!temp)
		return (0);
	temp->next = 0;
	temp->content = data;
	return (temp);
}

static void	ft_lstdelone_l(t_list *begin_list, void (*free_fct)(void *))
{
	free_fct(begin_list->content);
	free(begin_list);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*next;
	t_list	*temp;
	t_list	*mv;

	res = 0;
	while (lst)
	{
		next = lst->next;
		temp = ft_create_elem(f(lst->content));
		if (!temp)
			return (0);
		if (!res)
			res = temp;
		else
			mv->next = temp;
		mv = temp;
		ft_lstdelone_l(lst, del);
		lst = next;
	}
	return (res);
}
