#include "minishell.h"

void	*ft_env(void **ptr)
{
	t_env_list	**env;

	env = (t_env_list **)ptr;
	if (!env || !*env)
		return (NULL);
	ft_print_env(env);
	return (ptr);
}

void	ft_print_export(t_env_list **env)
{
	t_env_list	*tmp;

	if(!env || !*env)
	{
		printf("in ft_print_export, enter the null env\n");
		return ;
	}
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

int	ft_env_is_exist(char *str, t_env_list **env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	tmp = ft_substr(str, 0, i);
	if (!tmp)
		return (0);
	if (ft_find_elm(env, tmp))
		return (1);
	free(tmp);
	return (0);
}

void	*ft_export(void *ptr, t_env_list **env)
{
	char	*str;
	t_env_list	*head;

	if (!ptr)
	{
		ft_print_export(env);
		exit_from_child (0, NULL, NULL, NULL);
		return (NULL);
	}
	str = (char *)ptr;
	if (ft_isvalid_name(str))
	{
		exit_from_child(1, "export", str, "not a valid identifier");
		return (ptr);
	}
	if (ft_env_is_exist(str, env))
	{
		printf("env deja existed!\n");
		return (ptr);
	}
	printf("---head %s=%s|\n", (*env)->key, (*env)->val);
	head = *env;
	while ((*env)->next != NULL)
	{
		*env = (*env)->next;
	}
	(*env)->next = ft_env_lstnew(str);
	*env = head;
	return (ptr);
}