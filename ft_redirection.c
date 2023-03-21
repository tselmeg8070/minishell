#include "minishell.h"

/*
Cases:
	Basic:
		< 'Tselmeg is'
		< $TEST
	Edge:
		export $TEST="Running lion"
		echo tselmeg > $TEST // bash: $test: ambiguous redirect
		echo tselmeg > "$TEST" // works
		echo tselmeg > // bash: syntax error near unexpected token `newline'
*/

int	ft_check_filename_eof(char c, int quote)
{
	if (quote == 0 && (c == ' ' || c == '<' || c == '\t' || c == '>'))
		return (0);
	return (1);
}

int	ft_local_quoter(char c, int *quote)
{
	if (*quote == 0 && c == '\'')
	{
		*quote = 1;
		return (1);
	}
	else if (*quote == 0 && c == '\"')
	{
		*quote = 2;
		return (1);
	}
	else if ((*quote == 1 && c == '\'') || (*quote == 2 && c == '\"'))
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

char	*ft_get_filename(char *str, t_env_list *env)
{
	int		i;
	int		quote;
	char	*res;

	i = 0;
	quote = 0;
	res = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && ft_check_filename_eof(str[i], quote))
	{
		if (ft_local_quoter(str[i], &quote))
			i++;
		else if ((quote == 0 || quote == 2) && str[i] == '$')
			i = ft_string_creation(str, &res, i, env);
		else
			ft_concat_char(&res, str[i++]);
	}
	return (res);
}

int	ft_inout_balancer(char *str, int start)
{
	char	*token;
	int		l;
	t_list	*ins;
	t_list	*outs;

	l = 0;
	ins = 0;
	outs = 0;
	token = ft_substr(str, start, 2);
	if (ft_strcmp(">>", token))
		l = ft_red_output(2, outs);
	else if (ft_strcmp("<<", token))
		l = ft_red_input(2, ins);
	free(token);
	token = ft_substr(str, start, 1);
	if (ft_strcmp(">", token))
		l = ft_red_output(1, outs);
	else if (ft_strcmp("<", token))
		l = ft_red_input(1, ins);
	free(token);
	return (l);
}

// char	*ft_define_redirections(char *str, t_env_list *env)
// {
// 	int		quote;
// 	int		i;
// 	char	*res;

// 	quote = 0;
// 	i = 0;
// 	res = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (quote == 0 && str[i] == '\'')
// 			quote = 1;
// 		else if (quote == 0 && str[i] == '\"')
// 			quote = 2;
// 		else if ((quote == 1 && str[i] == '\'')
// 			|| (quote == 2 && str[i] == '\"'))
// 			quote = 0;
// 		else if (quote == 0)
// 		{

// 		}
// 		i++;
// 	}
// 	return (res);
// }
