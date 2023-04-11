/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galtange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:07:02 by galtange          #+#    #+#             */
/*   Updated: 2023/04/11 17:38:51 by galtange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_status(void)
{
	printf("0");
	return (2);
}

int	ft_shell_var(char nbr)
{
	if (nbr == '0')
		printf("name_of_shell");
	return (2);
}

int	ft_print_format(char *str, t_env_list **envs)
{
	t_env_list	*tmp;
	int			i;

	i = 0;
	if (str[i] == '?')
		return (ft_exit_status());
	if (ft_isdigit(str[i]))
		return (ft_shell_var(str[i]));
	while (ft_isalnum(str[i]))
		i++;
	if (i != 0)
	{
		tmp = *envs;
		while (tmp != NULL)
		{
			if (!ft_strncmp(str, tmp->key, i))
				printf("%s", tmp->val);
			tmp = tmp->next;
		}
		return (i + 1);
	}
	return (0);
}

void	ft_print_echo(char *str, t_env_list **envs)
{
	int	i;
	int	skip;

	i = 0;
	while (str[i] != '\0')
	{
		skip = 0;
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			skip = ft_print_format(&str[i + 1], envs);
			i += skip;
		}
		printf("%c", str[i]);
		i++;
	}
}

void	ft_echo(void **strs, t_env_list **envs)
{
	char	**tmp;
	int		flag_n;

	if (!strs || !*strs)
	{
		printf("\n");
		return ;
	}
	if (!envs || !*envs)
		return ;
	flag_n = 1;
	tmp = (char **)strs;
	if (*tmp && !ft_strncmp(*tmp, "-n", ft_strlen(*tmp)))
	{
		flag_n = 0;
		if (tmp + 1)
			tmp++;
	}
	while (*tmp != NULL)
	{
		ft_print_echo(*tmp, envs);
		tmp++;
	}
	if (flag_n)
		printf("\n");
}

// int ft_comp(char *str, char *str_cmp)
// {
//     int i;

//     i = 0;
//     if (ft_strlen(str) != ft_strlen(str_cmp))
//         return(1);
//     while (str[i])
//     {
//         if (str[i] != str_cmp[i])
//             return (1);
//         i++;
//     }
//     return (0);
// }

// int	if_strhasdollar(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != 0)
// 	{
// 		if (str[i] == '$')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
