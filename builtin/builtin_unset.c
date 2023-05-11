/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galtange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 21:53:31 by galtange          #+#    #+#             */
/*   Updated: 2023/05/01 21:56:19 by galtange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_var_unset(t_env_list **envs, char *str)
{
	t_env_list	*tmp;
	t_env_list	*head;

	head = *envs;
	tmp = *envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, str))
		{
			ft_delete_elm(envs, str);
			break ;
		}
		tmp = tmp->next;
	}
	envs = &head;
}

int	ft_unset(char **str, t_env_list **envs)
{
	int	i;

	i = 0;
	if (!envs || !*envs)
	{
		write(2, "minishell: unset: No such file or directory\n", 45);
		return (127);
	}
	else
	{
		while (str[i] != NULL)
		{
			if (ft_strcmp(str[i], "$?"))
				ft_var_unset(envs, str[i]);
			i++;
		}
	}
	return (0);
}
