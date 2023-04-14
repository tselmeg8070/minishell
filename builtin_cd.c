/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galtange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:29:55 by galtange          #+#    #+#             */
/*   Updated: 2023/04/14 19:32:43 by galtange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_strs(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_cd(char **str)
{
	int		i;
	char	*path;

	if (!str)
		i = 0;
	else
		i = ft_count_strs(str);
	path = NULL;
	if (i > 1)
		printf("minishell: cd: too many arguments\n");
	else if (i == 0)
		path = ft_strdup(getenv("HOME"));
	else if (!ft_strncmp(*str, "~", 1))
			path = ft_strjoin(getenv("HOME"), &str[0][1]);
	else
			path = ft_strdup(*str);
	if (!path)
		return ;
	if (chdir(path))
		printf("minishell: cd: %s: No such file or directory\n", *str);
	if (path)
		free (path);
}

// void	ft_cd(char **str)
// {
// 	int		i;
// 	char	*path;

// 	if (!str)
// 		i = 0;
// 	else
// 		i = ft_count_strs(str);
// 	path = NULL;
// 	if (i > 1)
// 		printf("minishell: cd: too many arguments\n");
// 	else if (i == 0)
// 		path = ft_strdup(getenv("HOME"));
// 	else if (i == 1)
// 	{
// 		if (!ft_strncmp(*str, "~", 1))
// 			path = ft_strjoin(getenv("HOME"), &str[0][1]);
// 		else
// 			path = ft_strdup(*str);
// 	}
// 	if (!path)
// 		return ;
// 	if (chdir(path))
// 		printf("minishell: cd: %s: No such file or directory\n", *str);
// 	if (path)
// 		free (path);
// }

// Change directory using an absolute path  | OK
// Change directory using a relative path   | OK
// Change to the home directory "cd ~ "     | OK 
// Change to the previous directory "cd -"  | NOK
// cd ../../                                | OKs
// Change to the root directory "cd / "     | OK
// Change to another user's home directory  "cd ~username" | ?
// Change to Directory having Spaces "../ minishell" | OK
// Change up to multiple Sub Directories    | OK
// cd .   -do nothing                       | OK
// ~/work/solong/minilibx-linux/man/man1    | OK

// wrong path                               
// .~/work/solong/minilibx-linux/man/man1   | OK  

// void    ft_cd(void **ptr)
// {
//     int i;
//     char    **str;

//     if (!ptr || !*ptr)
//     {
//         chdir(getenv("HOME"));
//         return ;
//     }
//     i = 0;
//     str = (char **) ptr;
//     while (str[i])
//         i++;
//     if (i != 1)
//     {
//         printf("minishell: cd: too many arguments\n");
//         return ;
//     }
// 	if (!ft_strncmp(*str, "", ft_strlen(*str))
// 		|| !ft_strncmp(*str, "~", ft_strlen(*str)))
// 	{
// 		chdir(getenv("HOME"));
// 	}
//     else if (!ft_strncmp(*str, "-", ft_strlen(*str)))
// 	{
// 		if (chdir("-"))
//             printf("test failed\n");
//             return ;
// 	}
//     else if (chdir(*str))
// 	{
// 		printf("minishell: cd: %s: No such file or directory\n", *str);
// 	}
// }

// void	*ft_cd(void **ptr, t_env_list **env)
// {
// 	int		i;
// 	char	**str;

// 	i = 0;
// 	str = (char **)ptr;
// 	while (ptr[i])
// 		i++;
// 	if (i != 1)
// 	{
// 		printf("minishell> cd: too many arguments\n");
// 		return (NULL);
// 	}
// 	if (!ft_strncmp(*str, "", ft_strlen(*str))
// 		|| !ft_strncmp(*str, "~", ft_strlen(*str)))
// 	{
// 		chdir(getenv("HOME"));
// 	}
// 	else
// 	{
// 		printf("cd: %s: No such file or directory\n", *str);
// 		return (NULL);
// 	}
// 	return (ptr);
// }
