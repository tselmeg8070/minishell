/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:01:14 by galtange          #+#    #+#             */
/*   Updated: 2023/05/12 00:55:56 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_print_envlist(t_env_list **env)
{
	t_env_list	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		write (1, "declare -x ", 12);
		write (1, tmp->key, ft_strlen(tmp->key));
		if (tmp->val != NULL)
		{
			write (1, "=\"", 2);
			write (1, tmp->val, ft_strlen(tmp->val));
			write (1, "\"", 1);
		}
		write (1, "\n", 1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_name_notvalid(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
	{
		write (2, "export: `", 10);
		write (2, str, ft_strlen(str));
		write (2, "': not a valid identifier\n", 27);
		return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			write (2, "export: `", 10);
			write (2, str, ft_strlen(str));
			write (2, "': not a valid identifier\n", 27);
			return (1);
		}
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
	if (i == (int) ft_strlen(path))
	{
		new->key = ft_strdup(path);
		if (!new->key)
		{
			free (new);
			return (NULL);
		}
		new->val = NULL;
	}
	else
		new = ft_env_lstnew(path);
	return (new);
}

int	ft_export_env(t_env_list **envs, char *str)
{
	t_env_list	*tmp;
	t_env_list	*new;

	tmp = *envs;
	new = ft_envcreate(str);
	if (!new)
		return (1);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, new->key))
		{
			if (new->val != NULL)
			{
				tmp->val = ft_strdup(new->val);
				if (!tmp->val)
					return (ft_del_return(new, 1));
			}
			ft_del_node(new);
			return (0);
		}
		tmp = tmp->next;
	}
	ft_add2list(envs, ft_envcreate(str));
	ft_del_node(new);
	return (0);
}

int	ft_export(char **str, t_env_list **envs)
{
	int	i;

	if (!envs || !*envs)
	{
		write(2, "minishell> export: No such file or directory\n", 46);
		return (127);
	}
	if (str && !ft_strcmp(*str, "export"))
		str++;
	if (!*str)
		return (ft_print_envlist(envs));
	i = 0;
	while (*str)
	{
		if (ft_name_notvalid(*str) != 0)
			i = 1;
		else
		{
			if (ft_export_env(envs, *str))
				return (1);
		}
		str++;
	}
	return (i);
}
