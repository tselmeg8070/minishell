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

#include "minishell.h"

void	ft_var_found(t_env_list **envs, char *str)
{
	t_env_list	*tmp;
	t_env_list	*head;

	head = *envs;
	tmp = *envs;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
			ft_delete_elm(envs, str);
		tmp = tmp->next;
	}
	envs = &head;
}

void	ft_unset(char **str, t_env_list **envs)
{
	int	i;

	i = 0;
	if (!envs || !*envs)
		printf("in ft_print_export, enter the null env list\n");
	else
	{
		while (str[i] != NULL)
		{
			ft_var_found(envs, str[i]);
			i++;
		}
	}
}
