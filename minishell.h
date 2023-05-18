/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 00:15:45 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/18 22:43:42 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <curses.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>

extern int	g_status[2];

typedef struct s_env_list
{
	char				*key;
	char				*val;
	struct s_env_list	*next;
}						t_env_list;

/*
	2 - > - redirect output
	3 - < - redirect input file
	4 - >> - redirect output using append
	5 - << - call heredoc with ending condition
*/
typedef struct s_redirection
{
	int					type;
	char				*filename;
	char				*original;
}						t_redirection;

typedef struct s_data
{
	t_list		*tokens;
	t_list		*command_table;
	char		*line;
	t_env_list	*env;
}						t_data;

typedef struct s_instruction
{
	int					pid;
	int					in;
	int					out;
	int					pipe[2];
	int					redirection[2];
	int					err_code;
	char				*err_msg;
	char				**val;
	int					valc;
	t_list				*commands;
	t_list				*tokens;
	t_list				*files;
}						t_instruction;

void					ft_quotation_error(t_env_list **env);

void					ft_ensure_pipe_error(t_data **data);

void					ft_ensure_pipe_mem_error(t_data **data);

void					ft_line_loop(int *res, t_data **data);

int						ft_add2list(t_env_list **list, t_env_list *n_elm);

char					*ft_find_elm(t_env_list **list, char *key);

void					ft_delete_elm(t_env_list **list, char *key);

int						ft_free_envlst(t_env_list **list);

t_env_list				*ft_env_lstnew(char *path);

void					ft_del_node(t_env_list *elm);

void					ft_split_free(char ***res);

void					ft_pipe_to_link(t_instruction *inst, int *link);

int						ft_quote_check(char *str);

char					**ft_split_pipe(char const *strp, char charset);

char					*ft_replace_env(char *str, t_env_list *env);

t_env_list				*ft_create_envlist(char **paths);

void					ft_printlist(t_env_list **list);

int						ft_strcmp(char *s1, char *s2);

void					ft_concat_char(char **str, char c);

int						ft_concat_char_protected(char **token, char c);

void					ft_concat_empty(char **val);

int						ft_string_creation(char *str, char **res, int i,
							t_env_list *env);

int						ft_quoter(char c, int quote);

int						ft_local_quoter(char c, int *quote);

int						ft_handle_redirection(t_instruction *inst);

int						ft_tokenize(char *line, t_list **list);

int						ft_is_token(char c);

int						ft_token_check(t_list *list);

t_instruction			*ft_init_instruction(void);

t_list					*ft_init_instructions(void);

t_instruction			*ft_get_instuction(t_list *list);

void					ft_add_instruction(t_list **list);

void					ft_free_instruction(void *inst);

t_list					*ft_token_seperation(t_list *token);

int						ft_lstadd_back_safe(t_list **list, void *content);

int						ft_handle_instruction_redirection(t_list *inst);

int						ft_handle_env_command(t_list *inst_table,
							t_env_list *env);

int						ft_handle_env_redirection(t_list *inst_table,
							t_env_list *env);

int						ft_lstlen(t_list *head);

int						ft_generate_char_list_traverse(t_list *table);

char					*ft_strip(char *token);

int						ft_quote_strip(t_instruction *inst);

int						ft_quote_strip_traverse(t_list *table);

int						ft_execute_loop(char **paths, t_data **data,
							int *link);

int						ft_check_ambiguous(t_instruction *inst,
							t_redirection *red);

void					ft_redirection_file(t_instruction *inst,
							t_redirection *red);

int						ft_handle_redirection_err(t_instruction *inst);

int						ft_command_redirection(t_instruction *inst);

int						ft_check_red_permission(t_instruction *inst,
							t_redirection *red);

int						ft_call_execution(t_data **data);

int						ft_check_access(char **paths, char *arr);

void					ft_write_result(int out, int fd);

void					ft_history(char *line);

int						ft_aff_msg(int fd, char *str, int exit_val);

void					ft_init_sig(struct sigaction *sa);

int						ft_builtin_check(char **vals);

int						ft_builtin_caller(char **args, t_env_list **env_list);

int						ft_echo(char **strs);

int						ft_pwd(char **strs);

int						ft_env(t_env_list **envs);

int						ft_export(char **str, t_env_list **envs);

int						ft_unset(char **str, t_env_list **envs);

int						ft_cd(char **str, t_env_list **envs);

void					ft_exit_status(int exit_status, t_env_list **envs);

int						ft_exit_bt(char **str);

int						ft_count_strs(char **str);

int						ft_lexa_parse(t_data **data);

char					**ft_env_convert_original(t_env_list *env);

int						ft_only_spaces(char *line);

int						ft_execute(char **paths, t_instruction *inst,
							t_data **data);

t_data					*ft_init_data(void);

void					ft_free_data(t_data **data);

void					ft_wait_execution(t_list *cmd_table, int *status);

void					ft_init_signals(void);

void					ft_sig_from_child(int sig);

void					ft_child_sigint(void);

int						ft_del_return(t_env_list *node, int ret);

void					ft_start_pipe_error(t_data **data);

int						ft_gen_error_msg(t_instruction *inst, char *name,
							int id);

#endif
