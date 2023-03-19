#include "minishell.h"

int		ft_inout_balancer(char *str, int start)
{
	char	*token;
	int		l;

	l = 0;
	token = ft_substr(str, start, 2);
	if (ft_strcmp(">>", token))
		l = ft_inout_append();
	else if (ft_strcmp("<<", token))
		l = ft_inout_heredoc();
	free(token)
	token = ft_substr(str, start, 1);
	if (ft_strcmp(">", token))
		l = ft_inout_create();
	else if (ft_strcmp("<", token))
		l = ft_inout_read();
	free(token);
	return (l);
}

char	*ft_define_in_out(char *str, t_env_list *env)
{
	int		quote;
	int		i;
	char	*res;

	quote = 0;
	i = 0;
	res = 0;
	while (str[i] != '\0')
	{
		if (quote == 0 && str[i] == '\'')
			quote = 1;
		else if (quote == 0 && str[i] == '\"')
			quote = 2;
		else if ((quote == 1 && str[i] == '\'')
			|| (quote == 2 && str[i] == '\"'))
			quote = 0;
		else if (quote == 0)
		{

		}
		i++;
	}
	return (res);
}
