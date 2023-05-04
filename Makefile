# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 16:51:42 by tadiyamu          #+#    #+#              #
#    Updated: 2023/02/05 16:51:46 by tadiyamu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = minishell
CC = cc
CFLAGSDD = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
FILES = minishell \
		minishell_utils \
		minishell_utils2 \
		ft_replace_env \
		ft_split_pipe\
		ft_env_list\
		ft_tokenize\
		ft_token_check\
		ft_instruction\
		ft_create_command\
		ft_generate_char_list\
		ft_quote_strip\
		ft_redirection\
		get_next_line/get_next_line\
		get_next_line/get_next_line_utils\
		ft_command_execution\
		command_redirection/ft_redirection_ambiguous\
		command_redirection/ft_redirection_file\
		command_redirection/ft_redirection_loop\
		command_redirection/ft_redirection_permission\
		ft_env_list_utils

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $^ -L./libft -lft -Lreadline -lreadline

$(LIBFT):
	make -C libft
	make bonus -C libft

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	make clean -C libft
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(NAME_B)

re: fclean all
