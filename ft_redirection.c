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

/*
Compares with
*/
int	ft_inout_balancer(char *str, t_list **files)
{
	char	*token1;
	char	*token2;
	int		l;

	l = 0;
	token1 = ft_substr(str, 0, 2);
	token2 = ft_substr(str, 0, 1);
	if (ft_strcmp(">>", token1) == 0)
		l = ft_red_filename(str + 2, 4, files);
	else if (ft_strcmp("<<", token1) == 0)
		l = ft_red_filename(str + 2, 5, files);
	else if (ft_strcmp(">", token2) == 0)
		l = ft_red_filename(str + 1, 2, files);
	else if (ft_strcmp("<", token2) == 0)
		l = ft_red_filename(str + 1, 3, files);
	if (l == 0)
	{
		free(token1);
		free(token2);
		return (-1);
	}
	if (ft_strcmp(">>", token1) == 0 || ft_strcmp("<<", token1) == 0)
		l += 2;
	else if (ft_strcmp(">", token2) == 0 || ft_strcmp("<", token2) == 0)
		l++;
	free(token1);
	free(token2);
	return (l);
}

int	ft_handle_redirection(char *str, t_instruction *inst)
{
	char	*token1;
	char	*token2;
	int		l;

	l = 0;
	token1 = ft_substr(str, 0, 2);
	token2 = ft_substr(str, 0, 1);
	if (ft_strcmp(">>", token1) == 0)
		l = ft_red_filename(str + 2, 4, &inst->files);
	else if (ft_strcmp("<<", token1) == 0)
		l = ft_red_filename(str + 2, 5, &inst->files);
	else if (ft_strcmp(">", token2) == 0)
		l = ft_red_filename(str + 1, 2, &inst->files);
	else if (ft_strcmp("<", token2) == 0)
		l = ft_red_filename(str + 1, 3, &inst->files);
	if (l == 0)
	{
		inst->err_msg = ft_strdup("Unexpected new line");
		inst->err_code = 1;
	}
	if (ft_strcmp(">>", token1) == 0 || ft_strcmp("<<", token1) == 0)
		l += 2;
	else if (ft_strcmp(">", token2) == 0 || ft_strcmp("<", token2) == 0)
		l++;
	free(token1);
	free(token2);
	return (l);
}

// void	ft_check_list(void *file)
// {
// 	t_redirection *temp = (t_redirection*) file;
// 	printf("File: %s Type: %d\n", temp->filename, temp->type);
// }

// int		ft_define_redirections(t_instruction *inst, t_env_list *env)
// {
// 	int		quote;
// 	int		i;
// 	int		d;
// 	char	*res;

// 	quote = 0;
// 	res = 0;
// 	i = 0;
// 	while (inst->val[i] != '\0')
// 	{
// 		ft_local_quoter(inst->val[i], &quote);
// 		if (quote == 0 && (inst->val[i] == '<' || inst->val[i] == '>'))
// 		{
// 			d = ft_inout_balancer(inst->val + i, env, &inst->files);
// 			if (d <= 0)
// 				printf("minishell: syntax error near unexpected token `newline'\n");
// 		}
// 		if (d > 0)
// 		{
// 			i += d;
// 			d = 0;
// 		}
// 		else
// 			ft_concat_char(&res, inst->val[i++]);
// 	}
// 	free(inst->val);
// 	inst->val = res;
// 	ft_lstiter(inst->files, ft_check_list);
// 	return (1);
// }
