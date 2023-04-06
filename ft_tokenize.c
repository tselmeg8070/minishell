#include "minishell.h"

int	ft_is_token(char c)
{
	if (c == '/' || c == '>' || c == '<')
		return (1);
	if (c == '|' || c == '&')
		return (1);
	return (0);
}

/*
Adds token to token list
Fallback:
	(0) - Memory allocation fails
*/
int	ft_add_token(char **token, t_list **list)
{
	t_list	*node;

	node = ft_lstnew(*token);
	if (node)
		ft_lstadd_back(list, node);
	else
		return (0);
	*token = 0;
	return (1);
}

/*
Funcion to put redirection token to token list
Fallback:
	(-1) - Memory allocaion fails
*/
int	ft_token_to_list(char *line, t_list **list)
{
	char	*string;

	string = 0;
	if (line[0] == '<' && line[1] && line[1] == '<')
	{
		string = ft_strdup("<<");
		if (string && ft_add_token(&string, list))
			return (1);
	}
	else if (line[0] == '>' && line[1] && line[1] == '>')
	{
		string = ft_strdup(">>");
		if (string && ft_add_token(&string, list))
			return (1);
	}
	else
	{
		ft_concat_char(&string, line[0]);
		if (string && ft_add_token(&string, list))
			return (0);
	}
	return (-1);
}

/*
Tokeninzing process for non quoted string
Fallback:
	(-1) - Memory allocation fails
*/
int	ft_tokenize_process(char *line, t_list **list, char **token)
{
	if (ft_is_token(line[0]))
	{
		if (*token && !ft_add_token(token, list))
			return (-1);
		return (ft_token_to_list(line, list));
	}
	else if (line[0] == ' ' && *token != 0 && !ft_add_token(token, list))
		return (-1);
	else if (line[0] != ' ')
	{
		ft_concat_char(token, line[0]);
		if (*token == 0)
			return (-1);
	}
	return (0);
}

/*
Converts string into tokenized line
Fallback:
	(0) - Memory allocation fails
*/
int	ft_tokenize(char *line, t_list **list)
{
	char	*token;
	int		i;
	int		quote;
	int		c;

	token = 0;
	i = 0;
	quote = 0;
	while (line[i])
	{
		ft_local_quoter(line[i], &quote);
		if (quote == 0)
		{
			c = ft_tokenize_process(line + i, list, &token);
			if (c == -1)
				return (0);
			i += c;
		}
		else if (!ft_concat_char_protected(&token, line[i]))
			return (0);
		i++;
	}
	if (token)
		return (ft_add_token(&token, list));
	return (1);
}
