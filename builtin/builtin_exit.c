#include "../minishell.h"

int ft_exit_bt(char **str, t_env_list **envs)
{
    int exit_val;

    write (2, "exit\n", 5);
    if (!str || !*str)
    {

    }
    else if (ft_count_strs(str) > 1)
    {
        write (2, "minishell> exit: too many arguments\n", 37);
        return (1);
    }
    else
        exit_val = ft_atoi(*str) % 256;
    return (exit_val);
}