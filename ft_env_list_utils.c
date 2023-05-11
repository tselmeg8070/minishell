/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:22:33 by galtange          #+#    #+#             */
/*   Updated: 2023/05/09 23:22:12 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*ft_env_lstnew(char *path)
{
	t_env_list	*newnode;
	int			i;

	i = 0;
	newnode = (t_env_list *) malloc(sizeof(t_env_list));
	if (!newnode)
		return (NULL);
	while (path[i] != '=' && path[i])
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

	if (!paths || !*paths)
		return (NULL);
	env_list = ft_env_lstnew("?=0");
	if (!env_list)
		return (NULL);
	i = 0;
	while (paths[i])
		i++;
	while (--i >= 0)
	{
		if (ft_add2list(&env_list, ft_env_lstnew(paths[i])))
			return (NULL);
	}
	return (env_list);
}

void	ft_exit_status(int exit_status, t_env_list **envs)
{
	t_env_list	*tmp;
	char		*str;

	tmp = *envs;
	while(tmp)
	{
		if (ft_strcmp(tmp->key, "?") == 0)
		{
			str = tmp->val;
			tmp->val = ft_itoa(exit_status);
			free(str);
			break ;
		}
		tmp = tmp->next;
	}

}

// void	ft_printlist(t_env_list **list)
// {
// 	t_env_list	*tmp;

//     if (!list || !*list)
//     {
//         printf ("list empty!\n");
//         return;
//     }
//     tmp = *list;
//     while (tmp != NULL)
//     {
//         printf("%s=%s\n", tmp->key, tmp->val);
//         tmp = tmp->next;
//     }
// }
