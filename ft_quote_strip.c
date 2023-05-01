#include "minishell.h"

int	ft_get_quote_id(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

char	*ft_quote_strip_mem_fail(char **res)
{
	free(*res);
	return (0);
}

/*
Creates new string by stripping out most quotation mark
Fallback:
	(0/null) - Memory fails
*/
char	*ft_strip(char *token)
{
	int		i;
	char	*res;
	int		quote;

	res = 0;
	i = 0;
	quote = 0;
	while (token[i])
	{
		if (ft_get_quote_id(token[i]))
		{
			if (quote == ft_get_quote_id(token[i]))
				quote = 0;
			else if (quote == 0)
				quote = ft_get_quote_id(token[i]);
			else if (!ft_concat_char_protected(&res, token[i]))
				return (ft_quote_strip_mem_fail(&res));
		}
		else if (!ft_concat_char_protected(&res, token[i]))
			return (ft_quote_strip_mem_fail(&res));
		i++;
	}
	if (ft_strlen(res) == 0)
		ft_concat_empty(&res);
	return (res);
}

int	ft_quote_strip(t_instruction *inst)
{
	int		i;
	char	*temp;

	i = 0;
	while (inst->val[i])
	{
		temp = ft_strip(inst->val[i]);
		if (!temp)
			return (0);
		free(inst->val[i]);
		inst->val[i] = temp;
		i++;
	}
	inst->valc = i;
	return (1);
}

int	ft_quote_strip_traverse(t_list *table)
{
	while (table)
	{
		if (!ft_quote_strip(table->content))
			return (0);
		table = table->next;
	}
	return (1);
}
