
#include "minishell.h"

void	ft_try_every_path(char **paths, char **arr)
{
	char	*str;
	char	*joined;
	int		i;

	i = 0;
	while (arr && paths[i])
	{
		str = ft_strjoin(paths[i], "/");
		joined = ft_strjoin(str, arr[0]);
		free(str);
		execve(joined, arr, (char **){NULL});
		free(joined);
		i++;
	}
	execve(arr[0], arr, (char **){NULL});
	// ft_split_free(&arr);
}

int	ft_execute(char **paths, char **arr, int *link, int fd)
{
	if (fd >= 0)
	{
		dup2(fd, STDIN_FILENO);
		dup2(link[1], STDOUT_FILENO);
		close(link[0]);
		close(link[1]);
		close(fd);
		// if (ft_check_access(paths, arr))
		ft_try_every_path(paths, arr);
	}
	close(link[0]);
	close(link[1]);
	return (EXIT_FAILURE);
}

int	ft_execute_loop(char **paths, t_list *command_table, int fd, int *link)
{
	int pid;
	int status;
	t_instruction *inst;

	status = 1;
	while (command_table)
	{
		//check redirections
		pipe(link);
		pid = fork();
		if (pid == 0)
		{
			inst = (t_instruction *) command_table->content;
			return (ft_execute(paths, inst->val, link, fd));
		}
		waitpid(pid, &status, 0);
		close(link[1]);
		fd = link[0];
		command_table = command_table->next;
	}
	return (status);
}
