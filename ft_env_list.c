/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:25:02 by galtange          #+#    #+#             */
/*   Updated: 2023/05/19 00:11:42 by galtange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add2list(t_env_list **list, t_env_list *n_elm)
{
	if (!*list)
	{
		*list = n_elm;
		return (0);
	}
	if (!n_elm)
		return (1);
	n_elm->next = *list;
	*list = n_elm;
	return (0);
}

char	*ft_find_elm(t_env_list **list, char *key)
{
	t_env_list	*tmp;

	if (!list || !*list)
		return (NULL);
	tmp = *list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->val);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_del_node(t_env_list *elm)
{
	if (!elm)
		return ;
	if (elm->key)
		free(elm->key);
	if (elm->val)
		free (elm->val);
	free(elm);
}

void	ft_delete_elm(t_env_list **list, char *key)
{
	t_env_list	*head;
	t_env_list	*tmp;

	if (!list || !*list || !key)
		return ;
	head = *list;
	tmp = *list;
	if (ft_strcmp(tmp->key, key) == 0)
	{
		*list = tmp->next;
		ft_del_node(tmp);
		return ;
	}
	tmp = (*list)->next;
	while (ft_strcmp(tmp->key, key) && (*list)->next != NULL)
	{
		*list = (*list)->next;
		tmp = tmp->next;
	}
	(*list)->next = tmp->next;
	ft_del_node(tmp);
	*list = head;
}

int	ft_free_envlst(t_env_list **list)
{
	t_env_list	*tmp;

	if (!*list || !list)
		return (0);
	while (*list != NULL)
	{
		tmp = (*list)->next;
		ft_del_node(*list);
		*list = tmp;
	}
	return (0);
}

// char	*ft_find_elm(t_env_list **list, char *key)
// {
// 	t_env_list	*tmp;

// 	if (!list || !*list)
// 		return (NULL);
// 	tmp = *list;
// 	while (tmp->next != NULL)
// 	{
// 		if (ft_strcmp(tmp->key, key) == 0)
// 			return (tmp->val);
// 		else if (ft_strcmp("$?", key) == 0)
// 			return (ft_find_elm(list, "_exitcode"));
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }
