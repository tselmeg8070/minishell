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
NAME = pipex
NAME_B = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
FILES = pipex \
		pipex_access \
		pipex_util \
		pipex_child \
		get_next_line \
		get_next_line_utils

FILES_B = pipex_bonus \
		pipex_access_bonus \
		pipex_util_bonus \
		pipex_child_bonus \
		get_next_line \
		get_next_line_utils

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

SRCS_B = $(addsuffix .c, $(FILES_B))
OBJS_B = $(addsuffix .o, $(FILES_B))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $^ -L./libft -lft

bonus: $(OBJS_B) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_B) $^ -L./libft -lft

$(LIBFT):
	make -C libft

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	make clean -C libft
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(NAME_B)

re: fclean all
