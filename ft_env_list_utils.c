/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galtange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 21:34:09 by galtange          #+#    #+#             */
/*   Updated: 2023/03/18 21:38:07 by galtange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*ft_env_lstnew(char *path)
{
	t_env_list	*newnode;
	int			i;

	i = 0;
	newnode = (t_env_list *)malloc(sizeof(t_env_list));
	if (!newnode)
		return (NULL);
	while (path[i] != '=')
		i++;
	newnode->key = ft_substr(path, 0, i);
	if (!newnode->key)
		return (NULL);
	newnode->val = ft_strdup(path + (i + 1));
	if (!newnode->val)
		return (NULL);
	newnode->next = NULL;
	return (newnode);
}

t_env_list	*ft_create_envlist(char **paths)
{
	int			i;
	t_env_list	*env_list;

	i = 0;
	while (paths[i])
		i++;
	env_list = NULL;
	while (--i >= 0)
	{
		if (ft_add2list(&env_list, ft_env_lstnew(paths[i])))
			return (NULL);
	}
	if (!env_list)
		return (NULL);
	return (env_list);
}

void	ft_print_env(t_env_list **list)
{
	t_env_list	*tmp;

	if (!list || !*list)
	{
		printf ("list empty!\n");
		return ;
	}
	tmp = *list;
	while (tmp != NULL)
	{
		printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}
