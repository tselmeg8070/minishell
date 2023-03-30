#include "minishell.h"

int	ft_check_filename_eof(char c, int quote)
{
	if (quote == 0 && (c == ' ' || c == '<' || c == '\t' || c == '>'))
		return (0);
	return (1);
}

/*
Gets a filename from string
Cases:
	"test.txt"
	$test
	'test with space'
	'test $test'
	"$test"
Fallbacks:
	MEM fail: null
*/
char	*ft_get_filename(char *str, t_env_list *env, int *s)
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
		ft_local_quoter(str[i], &quote);
		ft_concat_char(&res, str[i++]);
		if (!res)
			return (res);
	}
	*s = i;
	return (res);
}

/*
Assign filename to structure and adds it to list
Fallback:
	No file name found: 0
	MEM fail: 0
*/
int	ft_red_filename(char *str, int type, t_env_list *env, t_list **list)
{
	int				i;
	t_redirection	*redirection;
	t_list			*node;

	redirection = malloc(sizeof(t_redirection));
	if (!redirection)
		return (0);
	redirection->filename = ft_get_filename(str, env, &i);
	if (!redirection->filename)
	{
		free(redirection);
		return (0);
	}
	redirection->type = type;
	node = ft_lstnew(redirection);
	ft_lstadd_back(list, node);
	return (i);
}
