/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galtange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:08:12 by galtange          #+#    #+#             */
/*   Updated: 2023/03/21 16:22:22 by galtange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echoplus(char *str)
{
	int	printed;

	printed = 0;
	if (ft_strncmp(str, "*", ft_strlen(str)))
		printed += printf("ls");
	else if (str[0] == '$' && str[1] != '\0')
		printed += printf("%s", getenv(&str[1]));
	else
		printed += printf("%s", str);
	return (printed);
}

void	*ft_echo(void **ptr)
{
	char	**str;
	int		n_line;
	int		printed;
	int		i;

	str = (char **)ptr;
	n_line = 1;
	printed = 0;
	i = 0;
	if (str[i] && !(ft_strncmp(str[i], "-n", ft_strlen(str[i]))))
	{
		n_line = 0;
		i++;
	}
	while (str[i])
	{
		printed = ft_echoplus(str[i]);
		if (str[i + 1] && printed != 0)
			printf(" ");
		i++;
	}
	if (n_line == 1)
		printf("\n");
	return (ptr);
}

void	*ft_cd(void **ptr, t_env_list **env)
{
	int		i;
	char	**str;

	i = 0;
	str = (char **)ptr;
	while (ptr[i])
		i++;
	if (i != 1)
	{
		printf("minishell> cd: too many arguments\n");
		return (NULL);
	}
	if (!ft_strncmp(*str, "", ft_strlen(*str))
		|| !ft_strncmp(*str, "~", ft_strlen(*str)))
	{
		chdir(getenv("HOME"));
	}
	else
	{
		printf("cd: %s: No such file or directory\n", *str);
		return (NULL);
	}
	return (ptr);
}
