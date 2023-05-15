/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:15:38 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/15 19:50:05 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*ft_init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == 0)
		return (0);
	data->env = 0;
	data->line = 0;
	data->command_table = 0;
	data->tokens = 0;
	return (data);
}

void	ft_free_data(t_data **data)
{
	if (*data == 0)
		return ;
	if ((*data)->tokens)
		ft_lstclear(&((*data)->tokens), free);
	if ((*data)->command_table)
		ft_lstclear(&((*data)->command_table), ft_free_instruction);
	if ((*data)->line)
		free((*data)->line);
	if ((*data)->env)
		ft_free_envlst(&((*data)->env));
	free(*data);
	*data = 0;
}
