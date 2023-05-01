#include "minishell.h"

int	ft_msg_token(char *token)
{
	printf("Unexpected token: %s\n", token);
	return (0);
}

int	ft_token_check_red(t_list *list)
{
	int		redirection;
	char	*token;
	char	*prev;

	redirection = 0;
	prev = 0;
	while (list)
	{
		token = (char *) list->content;
		if (ft_is_token(token[0]))
		{
			if (redirection)
				return (ft_msg_token(token));
			else if (token[0] == '<' || token[0] == '>')
				redirection = 1;
		}
		else
			redirection = 0;
		list = list->next;
		prev = token;
	}
	if (redirection)
		return (ft_msg_token("\\n"));
	return (1);
}

int	ft_token_check_pipe(t_list *list)
{
	int		pipe;
	char	*token;

	pipe = 0;
	while (list)
	{
		token = (char *) list->content;
		if (ft_is_token(token[0]))
		{
			if (pipe)
				return (ft_msg_token(token));
			else if (token[0] == '|')
				pipe = 1;
		}
		else
			pipe = 0;
		list = list->next;
	}
	if (pipe)
		return (ft_msg_token("|"));
	return (1);
}

int	ft_token_check(t_list *list)
{
	if (ft_token_check_red(list) == 0)
		return (0);
	if (ft_token_check_pipe(list) == 0)
		return (0);
	return (1);
}
