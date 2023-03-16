#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
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

typedef struct s_instruction {
	char	*val;
	int		type;
}	t_instruction;

void	ft_split_free(char ***res);

int		ft_quote_check(char *str);

char	**ft_split_pipe(char const *strp, char charset);

#endif
