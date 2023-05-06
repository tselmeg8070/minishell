/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:03:40 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/06 19:03:40 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Finds string based on key from env list and concats it to result.
Fallback:
	(-1) - memory fails
Return:
	(size) - size of the given key
*/
int	ft_string_creation(char *str, char **res, int i, t_env_list *env)
{
	int		l;
	char	*val;
	char	*key;
	char	*temp;

	i = i + 1;
	l = i;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i - l >= 1)
	{
		key = ft_substr(str, l, i - l);
		if (key && ft_strlen(key) > 0)
		{
			val = ft_find_elm(&env, key);
			temp = ft_strjoin(*res, val);
			if (*res)
				free(*res);
			*res = temp;
		}
		free(key);
		if (val != 0 && *res == 0)
			return (-1);
	}
	return (i);
}

/*
Replaces env variable in string.
Fallback:
	(null) - memory fails
*/
char	*ft_replace_env(char *str, t_env_list *env)
{
	int		quote;
	int		i;
	int		s;
	char	*res;

	quote = 0;
	i = 0;
	res = 0;
	while (str[i] != '\0')
	{
		quote = ft_quoter(str[i], quote);
		if ((quote == 0 || quote == 2) && str[i] == '$'
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			s = ft_string_creation(str, &res, i, env);
			if (s == -1)
				return (0);
			i = s;
		}
		else if (!ft_concat_char_protected(&res, str[i++]))
			return (0);
	}
	return (res);
}

/*
Expands command tokens in command table.
Fallback:
	(0) - memory fails
*/
int	ft_handle_env_command(t_list *inst_table, t_env_list *env)
{
	t_instruction	*inst;
	t_list			*token_list;
	char			*token;
	char			*expanded;

	while (inst_table)
	{
		inst = (t_instruction *) inst_table->content;
		token_list = (t_list *) inst->commands;
		while (token_list)
		{
			token = (char *) token_list->content;
			expanded = ft_replace_env(token, env);
			if (expanded == 0)
				return (0);
			free(token);
			token_list->content = expanded;
			token_list = token_list->next;
		}
		inst_table = inst_table->next;
	}
	return (1);
}

/*
Expands redirections in command table.
Fallback:
	(0) - memory fails
*/
int	ft_handle_env_redirection(t_list *inst_table, t_env_list *env)
{
	t_instruction	*inst;
	t_list			*file_list;
	t_redirection	*file;
	char			*expanded;

	while (inst_table)
	{
		inst = (t_instruction *) inst_table->content;
		file_list = (t_list *) inst->files;
		while (file_list)
		{
			file = (t_redirection *) file_list->content;
			if (file->type != 5)
			{
				expanded = ft_replace_env(file->filename, env);
				if (expanded == 0)
					return (0);
				file->original = (file->filename);
				file->filename = expanded;
			}
			file_list = file_list->next;
		}
		inst_table = inst_table->next;
	}
	return (1);
}
