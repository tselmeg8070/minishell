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
		ft_replace_env \
		ft_split_pipe\
		ft_env_list\
		ft_redirection\
		ft_redirection_utils\
		ft_env_list_utils

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $^ -L./libft -lft -Lreadline -lreadline

$(LIBFT):
	make -C libft
	make -C bonus

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	make clean -C libft
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(NAME_B)

re: fclean all
