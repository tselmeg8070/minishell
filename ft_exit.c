/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galtange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:30:04 by galtange          #+#    #+#             */
/*   Updated: 2023/03/19 17:32:07 by galtange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char *line, t_env_list **env)
{
	if (line)
		free(line);
	if (env)
		ft_free_envlst(env);
	printf("exit\n");
	return (EOF);
}
