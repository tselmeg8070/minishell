#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

/*
	0 - ''
	1 - ""
	2 - > - redirect output
	3 - < - redirect input file
	4 - >> - redirect output using append
	5 - << - call heredoc with ending condition
	6 - $ - call global variables or call command
	7 - | - Pipe
	8 - $? - exit status
	9 - && - AND operation
	10 - || - OR operation
	11 - () - Prioritization
	12 - * - Wildcard
*/

typedef struct s_env_list
{
    char            *key;
    char            *val;
    struct s_env_list   *next;
} t_env_list;

typedef struct s_instruction {
	char	*val;
	int		type;
}	t_instruction;

//ft for linked list
int	ft_add2list(t_env_list **list, t_env_list *n_elm);
char	*ft_find_elm(t_env_list **list, char *key);
void	ft_delete_elm(t_env_list **list, char *key);
int	ft_free_envlst(t_env_list **list);
t_env_list	*ft_env_lstnew(char *path);

void	ft_split_free(char ***res);

int		ft_quote_check(char *str);

char	**ft_split_pipe(char const *strp, char charset);

char	*ft_replace_env(char *str, t_env_list *env);
// char	*ft_replace_env(char *str);

//+++
t_env_list  *ft_create_envlist(char **paths);

/*signal*/
// void ft_signal_test(int num);
void    ft_init_sig(struct sigaction    *sa);
int ft_exit(char *line, t_env_list **env);
void	ft_history(char *line);

//for test
void    ft_print_env(t_env_list **list);
void	exit_from_child(int	status, char *bltin, char *cmd, char *msg);
void	*ft_export(void *ptr, t_env_list **env);

#endif
