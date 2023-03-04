/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:22:40 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/29 13:22:46 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_list_last(t_list *begin_list)
{
	if (begin_list == 0)
		return (0);
	while (begin_list->next != 0)
		begin_list = begin_list->next;
	return (begin_list);
}

void	ft_lstadd_back(t_list **begin_list, t_list *new)
{
	t_list	*last;

	last = ft_list_last(*begin_list);
	if (last == 0)
		*begin_list = new;
	else
		last->next = new;
}
