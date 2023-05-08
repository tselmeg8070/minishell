/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galtange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:26:44 by galtange          #+#    #+#             */
/*   Updated: 2023/05/01 19:28:12 by galtange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env_list **envs)
{
	t_env_list	*tmp;

	if (!envs || !*envs)
	{
		write(1, "minishell: env: No such file or directory\n", 43);
		return (127);
	}
	tmp = *envs;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->key, "$?"))
			tmp = tmp->next;
		if (tmp->val != NULL)
			printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	return (0);
}
