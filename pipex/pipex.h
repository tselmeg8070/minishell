/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:18:41 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/01/31 17:18:42 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include "./libft/libft.h"
# include "get_next_line.h"

void	ft_split_free(char ***res);

int		ft_check_access(char **paths, char *arr);

int		ft_in_check_access(char *path);

int		ft_check_result(char *path, int fd, int *res);

void	ft_command_free(char ***res, char **joined);

char	**ft_get_paths(char **envp);

int		ft_cnt_split(char **arr);

int		ft_command_parse(char *str, char ***arg, char **joined);

int		ft_execute(char **paths, char *arr, int *link, int fd);

int		ft_execute_loop(char **paths, char **argv, int fd, int *link);

int		ft_check_result_bonus(char *path, int fd, int *res);

#endif
