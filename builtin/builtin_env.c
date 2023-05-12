/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:26:44 by galtange          #+#    #+#             */
/*   Updated: 2023/05/12 03:04:05 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env_list **envs)
{
	t_env_list	*tmp;

	if (!envs || !*envs)
	{
		write(2, "minishell> env: No such file or directory\n", 43);
		return (127);
	}
	tmp = *envs;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->key, "?"))
			tmp = tmp->next;
		else
		{
			if (tmp->val)
			{
				ft_putstr_fd(tmp->key, 1);
				write(1, "=", 1);
				ft_putstr_fd(tmp->val, 1);
				write(1, "\n", 1);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

int	ft_env_list_size(t_env_list *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**ft_env_convert_original(t_env_list *env)
{
	char	**res;
	int		size;
	char	*temp;
	int		i;

	size = ft_env_list_size(env);
	i = 0;
	res = malloc(sizeof(char *) * (size + 1));
	res[size] = 0;
	while (res && env)
	{
		res[i] = ft_strdup(env->key);
		temp = res[i];
		res[i] = ft_strjoin(res[i], "=");
		free(temp);
		temp = res[i];
		res[i] = ft_strjoin(res[i], env->val);
		free(temp);
		env = env->next;
		i++;
	}
	return (res);
}
