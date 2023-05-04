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

void	ft_env(char **str, t_env_list **envs)
{
	t_env_list	*tmp;

	(void) str;
	if (!envs || !*envs)
		printf("in ft_print_export, enter the null env list\n");
	tmp = *envs;
	while (tmp->next)
	{
		if (tmp->val != NULL)
			printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}
