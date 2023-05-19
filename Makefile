# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 16:51:42 by tadiyamu          #+#    #+#              #
#    Updated: 2023/05/19 21:51:46 by tadiyamu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
LDFLAGS = -ltermcap -ltinfo
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
FILES = minishell \
		minishell_utils \
		minishell_utils2 \
		minishell_utils3 \
		minishell_logic \
		ft_line_handler \
		ft_line_handler_utils \
		ft_data_utils \
		ft_replace_env \
		ft_split_pipe\
		ft_env_list\
		ft_tokenize\
		ft_token_check\
		ft_instruction\
		ft_instruction_free\
		ft_create_command\
		ft_generate_char_list\
		ft_quote_strip\
		ft_redirection\
		get_next_line/get_next_line\
		get_next_line/get_next_line_utils\
		command_execution/ft_command_builtin\
		command_execution/ft_command_execution\
		command_execution/ft_command_execution_utils\
		command_execution/ft_command_call\
		command_execution/ft_command_permission\
		command_execution/ft_command_utils\
		command_redirection/ft_redirection_ambiguous\
		command_redirection/ft_redirection_heredoc\
		command_redirection/ft_redirection_file\
		command_redirection/ft_redirection_loop\
		command_redirection/ft_redirection_permission\
		command_redirection/ft_redirection_permission_utils\
		builtin/builtin_echo\
		builtin/builtin_pwd\
		builtin/builtin_env\
		builtin/builtin_export\
		builtin/builtin_unset\
		builtin/builtin_cd\
		builtin/builtin_cd_utils\
		builtin/builtin_exit\
		signal/ft_signal\
		ft_env_list_utils

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $^ -L./libft -lft -Lreadline -lreadline

$(LIBFT):
	make -C libft
	make bonus -C libft

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	make clean -C libft
	rm -f $(OBJS) $(OBJS_B)

valgrind:
	valgrind --suppressions=valgrind_readline_leaks_ignore.supp --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(NAME_B)

re: fclean all
