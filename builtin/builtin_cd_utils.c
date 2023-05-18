#include "../minishell.h"

int	ft_set_newpwd(t_env_list **envs)
{
	int			buff_size;
	char		*buffer;
	t_env_list	*tmp;

	buff_size = 4096;
	buffer = malloc(sizeof(char) * buff_size);
	if (!buffer)
		return (1);
	if (getcwd(buffer, buff_size) == NULL)
		return (1);
	tmp = *envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
            if (tmp->val)
			    free(tmp->val);
			tmp->val = ft_strdup(buffer);
			if (!tmp->val)
				return (1);
		}
		tmp = tmp->next;
	}
	free (buffer);
	return (0);
}

void    ft_set_oldpwd(t_env_list **envs, char *pwd)
{
    t_env_list  *cd_pwd;

    if (!ft_find_elm(envs, "OLDPWD"))
    {
        cd_pwd = (t_env_list *) malloc(sizeof(t_env_list));
        if (!cd_pwd)
            return ;
        cd_pwd->key = ft_strdup("OLDPWD");
        cd_pwd->val = ft_strdup(pwd);
        ft_add2list(envs, cd_pwd);
    }
    else
    {
        cd_pwd = *envs;
        while (cd_pwd)
        {
           	if (!ft_strcmp(cd_pwd->key, "OLDPWD"))
		    {
			    free(cd_pwd->val);
			    cd_pwd->val = ft_strdup(pwd);
				return ;
		    }
		    cd_pwd = cd_pwd->next;
        }
    }
}

int ft_set_pwds(t_env_list **envs)
{
    char    *old_pwd;
    t_env_list  *cd_pwd;

    old_pwd = ft_find_elm(envs, "PWD");
    if (!old_pwd)
    {
        ft_var_unset(envs, "OLDPWD");
        cd_pwd = (t_env_list *) malloc(sizeof(t_env_list));
        if (!cd_pwd)
            return (1);
        cd_pwd->key = ft_strdup("PWD");
        cd_pwd->val = NULL;
        ft_add2list(envs, cd_pwd);
    }
    else
        ft_set_oldpwd(envs, old_pwd);
    ft_set_newpwd(envs);
    return (0);
}