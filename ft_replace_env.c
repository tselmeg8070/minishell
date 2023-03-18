#include "minishell.h"

// char	*ft_find_from_env(char *key, t_env_list *env)
// {

// 	return ("tselmeg");
// }

void	ft_concat_char(char **str, char c)
{
	char	*res;
	int		len;

	if (*str == 0)
		len = 0;
	else
		len = ft_strlen(*str);
	res = malloc(len + 2);
	if (res)
	{
		ft_memcpy(res, *str, len);
		res[len + 1] = '\0';
		res[len] = c;
		free(*str);
	}
	*str = res;
}

int	ft_string_creation(char **str, char **res, int i, t_env_list *env)
{
	int		l;
	int		d;
	char	*val;
	char	*key;
	char	*temp;

	i = i + 1;
	l = i;
	while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == '_'))
		i++;
	if (i - l >= 1)
	{
		key = ft_substr(*str, l, i - l);
		if (ft_strlen(key) > 0)
		{
			val = ft_find_elm(&env, key);
			temp = ft_strjoin(*res, val);
			free(*res);
			*res = temp;
		}
		free(key);
	}
	return (i);
}

char	*ft_replace_env(char *str, t_env_list *env)
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
		if ((quote == 0 || quote == 2) && str[i] == '$')
			i = ft_string_creation(&str, &res, i, env);
		else
		{
			ft_concat_char(&res, str[i]);
			i++;
		}
	}
	return (res);
}
