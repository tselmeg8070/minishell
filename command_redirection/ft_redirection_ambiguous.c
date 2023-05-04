#include "../minishell.h"

/*
Generates error message and assigns that into instruction data structure
Fallback:
	(-1) - memory fails
*/
static int	ft_gen_error_msg(t_instruction *inst, char	*name)
{
	inst->err_code = 1;
	inst->err_msg = ft_strjoin(name, ": ambiguous redirect\n");
	if (!inst->err_msg)
		return (-1);
	return (0);
}

/*
Checks for ambiguous file name
Result:
	(0) - no errors
	(1) - errors
Fallback:
	(-1) - memory fail
*/
int	ft_check_ambiguous(t_instruction *inst, t_redirection *red)
{
	char	**result;
	int		i;

	if (red->type == 5)
		return (0);
	result = ft_split_pipe(red->filename, ' ');
	if (!result)
		return (-1);
	i = 0;
	while (result[i])
		i++;
	ft_split_free(&result);
	if (i != 1)
		return (ft_gen_error_msg(inst, red->original));
	return (0);
}
