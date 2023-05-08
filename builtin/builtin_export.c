/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:01:14 by galtange          #+#    #+#             */
/*   Updated: 2023/05/08 00:38:26 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_envlist(t_env_list **env)
{
	t_env_list	*tmp;

	if (!env || !*env)
		printf("in ft_print_export, enter the null env list\n");
	else
	{
		tmp = *env;
		while (tmp != NULL)
		{
			printf("declare -x ");
			printf("%s", tmp->key);
			if (tmp->val != NULL)
				printf("=\"%s\"", tmp->val);
			printf("\n");
			tmp = tmp->next;
		}
	}
}

int	ft_isvalid_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

t_env_list	*ft_envcreate(char *path)
{
	t_env_list	*new;
	int			i;

	i = 0;
	new = (t_env_list *) malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	while (path[i] != '\0' && path[i] != '=')
		i++;
	new->key = ft_substr(path, 0, i);
	if (!new->key)
		return (NULL);
	if (path[i] == '\0')
		new->val = NULL;
	else if (path[i] == '=')
		i++;
	new->val = ft_strdup(&path[i]);
	if (!new->val)
		return (NULL);
	return (new);
}

void	ft_export_env(t_env_list *new, t_env_list **envs)
{
	t_env_list	*tmp;

	tmp = *envs;
	while (tmp)
	{
		printf("1\n");
		if (ft_strcmp(tmp->key, new->key) == 0)
		{
			if (new->val != NULL)
				tmp->val = new->val;
			return ;
		}
		tmp = tmp->next;
	}
	tmp->next = new;
	new->next = NULL;
}

void	ft_export_test(char **str, t_env_list **envs)
{
	t_env_list	*tmp;

	if (!str || !*str)
		ft_print_envlist(envs);
	else
	{
		while (*str != NULL)
		{
			if (ft_isvalid_name(*str))
				printf ("export: `%s': not a valid identifier\n", *str);
			else
			{
				tmp = ft_envcreate(*str);
				if (!tmp)
				{
					printf("Err in envcreate\n");
					break ;
				}
				ft_export_env(tmp, envs);
			}
			str++;
		}
	}
}
