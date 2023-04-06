#include "minishell.h"

/*
Concats char to string.
Edge case:
	memory fail
	res: *str = null;
*/
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

int	ft_concat_char_protected(char **token, char c)
{
	ft_concat_char(token, c);
	if (token == 0)
		return (0);
	return (1);
}

int	ft_string_creation(char *str, char **res, int i, t_env_list *env)
{
	int		l;
	int		d;
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
		if (ft_strlen(key) > 0)
		{
			val = ft_find_elm(&env, key);
			temp = ft_strjoin(*res, val);
			if (*res)
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
		quote = ft_quoter(str[i], quote);
		if ((quote == 0 || quote == 2) && str[i] == '$')
			i = ft_string_creation(str, &res, i, env);
		else
			ft_concat_char(&res, str[i++]);
	}
	return (res);
}
