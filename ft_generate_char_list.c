/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_char_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:04:04 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/07 22:54:35 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_assign_tokens_list(char **tokens, t_list **res)
{
	int	i;

	i = 0;
	while (tokens && res && tokens[i] != 0)
	{
		if (!ft_lstadd_back_safe(res, ft_strdup(tokens[i])))
			return (0);
		i++;
	}
	return (1);
}

int	ft_tokens_list_to_char(t_instruction *inst, t_list *token)
{
	int		size;
	int		i;
	t_list	*next;

	i = 0;
	size = ft_lstlen(token);
	inst->val = malloc(sizeof(char *) * (size + 1));
	if (!inst->val)
		return (0);
	inst->val[size] = 0;
	while (token)
	{
		next = token->next;
		inst->val[i] = (char *) token->content;
		free(token);
		token = next;
		i++;
	}
	return (1);
}

/*
Converts command list into char** array to give to pipex.
Fallback:
	(0) - memory fails
*/
int	ft_generate_char_list(t_instruction *inst)
{
	t_list	*token;
	t_list	*res;
	char	**tokens;

	res = 0;
	tokens = 0;
	token = inst->commands;
	while (token)
	{
		tokens = ft_split_pipe(token->content, ' ');
		if (!tokens)
		{
			ft_lstclear(&res, free);
			return (0);
		}
		if (!ft_assign_tokens_list(tokens, &res))
		{
			ft_split_free(&tokens);
			return (0);
		}
		ft_split_free(&tokens);
		token = token->next;
	}
	return (ft_tokens_list_to_char(inst, res));
}

/*
Converts command list into char** array to give to pipex.
Fallback:
	(0) - memory fails
*/
int	ft_generate_char_list_traverse(t_list *table)
{
	while (table)
	{
		if (!ft_generate_char_list(table->content))
			return (0);
		table = table->next;
	}
	return (1);
}
