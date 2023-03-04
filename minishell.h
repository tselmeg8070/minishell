#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_stack {
	struct s_stack	*tail;
	int				val;
}	t_stack;

int		st_len(t_stack *a);

t_stack	*st_pop(t_stack **a);

t_stack	*st_create_node(int val);

int	st_push(t_stack **stack, int val);

void	st_clear(t_stack **stack);

#endif
