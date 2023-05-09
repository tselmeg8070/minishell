/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:26:44 by galtange          #+#    #+#             */
/*   Updated: 2023/05/09 17:17:23 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env_list **envs)
{
	t_env_list	*tmp;

	if (!envs || !*envs)
	{
		write(2, "minishell: env: No such file or directory\n", 43);
		return (127);
	}
	tmp = *envs;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->key, "$?"))
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

// {
// 	t_env_list	*tmp;

// 	if (!envs || !*envs)
// 	{
// 		write(2, "minishell: env: No such file or directory\n", 43);
// 		return (127);
// 	}
// 	tmp = *envs;
// 	while (tmp->next)
// 	{
// 		if (ft_strcmp(tmp->key, "$?"))
// 			tmp = tmp->next;
// 		else
// 		{
// 			if (tmp->val != NULL)
// 			{
// 				write (1, tmp->key, ft_strlen(tmp->key));
// 				write (1, "=", 1);
// 				write (1, tmp->val, ft_strlen(tmp->val));
// 			}
// 			tmp = tmp->next;
// 		}
// 	}
// 	return (0);
// }
