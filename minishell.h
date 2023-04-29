#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

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

/*
	2 - > - redirect output
	3 - < - redirect input file
	4 - >> - redirect output using append
	5 - << - call heredoc with ending condition
*/
typedef struct s_redirection {
	int		type;
	char	*filename;
}	t_redirection;

typedef struct s_instruction {
	int		in;
	int		out;
	int		err_code;
	char	*err_msg;
	char	**val;
	t_list	*commands;
	t_list	*tokens;
	t_list	*files;
}	t_instruction;

int		ft_add2list(t_env_list **list, t_env_list *n_elm);

char	*ft_find_elm(t_env_list **list, char *key);

void	ft_delete_elm(t_env_list **list, char *key);

int		ft_free_envlst(t_env_list **list);

void	ft_split_free(char ***res);

int		ft_quote_check(char *str);

char	**ft_split_pipe(char const *strp, char charset);

char	*ft_replace_env(char *str, t_env_list *env);

t_env_list	*ft_create_envlist(char **paths);

void	ft_printlist(t_env_list **list);

int		ft_strcmp(char *s1, char *s2);

void	ft_concat_char(char **str, char c);

int		ft_concat_char_protected(char **token, char c);

int		ft_string_creation(char *str, char **res, int i, t_env_list *env);

int		ft_quoter(char c, int quote);

int		ft_local_quoter(char c, int *quote);

int		ft_handle_redirection(t_instruction *inst);

int		ft_tokenize(char *line, t_list **list);

int		ft_is_token(char c);

int		ft_token_check(t_list *list);

t_instruction	*ft_init_instruction();

t_list			*ft_init_instructions();

t_instruction	*ft_get_instuction(t_list *list);

void	ft_add_instruction(t_list **list);

void	ft_free_instruction(void *inst);

t_list	*ft_token_seperation(t_list *token);

int		ft_lstadd_back_safe(t_list **list, void *content);

int		ft_handle_instruction_redirection(t_list *inst);

int		ft_handle_env_command(t_list *inst_table, t_env_list *env);

int		ft_handle_env_redirection(t_list *inst_table, t_env_list *env);

#endif
