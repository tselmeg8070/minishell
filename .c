#include "minishell.c"

void	ft_print_export(t_env_list **env)
{
	t_env_list	*tmp;

	if(!env || !*env)
		printf("in ft_print_export, enter the null env list\n");
	else
    {
    tmp = *env;
	while (tmp != NULL)
	{
		printf("declare -x ");
		printf("%s", tmp->key);
		if (ft_strncmp(tmp->val, "", ft_strlen(tmp->val)))
			printf("=\"%s\"", tmp->val);
		printf("\n");
		tmp = tmp->next;
	}
    }
}

// int	ft_isvalid_name(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!ft_isalpha(str[i]) && str[i] != '_')
// 		return (1);
// 	while (str[i] && str[i] != '=')
// 	{
// 		if (!ft_isalnum(str[i]) && str[i] != '_')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// void    ft_export_env(char *str, t_env_list **envs)
// {
//     (void) envs;
//     printf("we'll add %s\n", str);
// }
void	ft_export_bltn(char **strs, t_env_list **envs)
{
    // t_env_list *head;

    if (!strs || !*strs)
        ft_print_export(envs);
    while (*strs != NULL)
    {
        if (ft_isvalid_name(*strs))
            printf ("export: `%s': valid identifier\n", *strs);
        else
            ft_export_env(*strs, envs);
        strs++;
    }
}
