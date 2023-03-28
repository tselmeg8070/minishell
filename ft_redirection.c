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

int	ft_inout_balancer(char *str, t_env_list *env, t_list **files)
{
	char	*token1;
	char	*token2;
	int		l;

	l = 0;
	token1 = ft_substr(str, 0, 2);
	token2 = ft_substr(str, 0, 1);
	if (ft_strcmp(">>", token1) == 0)
		l += ft_red_filename(str + 2, 4, env, files) + 2;
	else if (ft_strcmp("<<", token1) == 0)
		l += ft_red_filename(str + 2, 5, env, files) + 2;
	else if (ft_strcmp(">", token2) == 0)
		l += ft_red_filename(str + 1, 2, env, files) + 1;
	else if (ft_strcmp("<", token2) == 0)
		l += ft_red_filename(str + 1, 3, env, files) + 1;
	free(token1);
	free(token2);
	return (l);
}

void	ft_check_list(void *file)
{
	t_redirection *temp = (t_redirection*) file;
	printf("File: %s Type: %d\n", temp->filename, temp->type);
}

char	*ft_define_redirections(char *str, t_env_list *env, t_list **files)
{
	int		quote;
	int		i;
	int		d;
	char	*res;

	quote = 0;
	i = 0;
	res = 0;
	while (str[i] != '\0')
	{
		ft_local_quoter(str[i], &quote);
		if (quote == 0)
			d = ft_inout_balancer(str + i, env, files);
		if (d > 0)
			i += d;
		else
		{
			ft_concat_char(&res, str[i]);
			i++;
		}
	}
	ft_lstiter(*files, ft_check_list);
	return (res);
}
