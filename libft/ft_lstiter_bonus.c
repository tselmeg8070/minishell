/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:29:34 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/29 13:40:00 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *begin_list, void (*f)(void *))
{
	while (begin_list != 0)
	{
		f(begin_list->content);
		begin_list = begin_list->next;
	}
}
