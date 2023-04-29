#include "minishell.h"

/*
Initializes the instruction
Fallback:
	(0/null) - Memory fails
*/
t_instruction	*ft_init_instruction()
{
	t_instruction	*inst;

	inst = malloc(sizeof(t_instruction));
	if (inst)
	{
		inst->val = 0;
		inst->in = 0;
		inst->out = 0;
		inst->err_msg = 0;
		inst->err_code = 0;
		inst->commands = 0;
		inst->files = 0;
		inst->tokens = 0;
	}
	return (inst);
}

void	ft_free_instruction(void *rinst)
{
	t_instruction	*inst;

	inst = (t_instruction *) rinst;
	ft_lstclear(&inst->tokens, free);
	free(inst);
}

t_list	*ft_init_instructions()
{
	t_list	*list;
	t_instruction	*inst;

	list = 0;
	inst = ft_init_instruction();
	if (inst)
	{
		list = ft_lstnew(inst);
		if (!list)
			free(inst);
		return (list);
	}
	return (0);
}

t_instruction *ft_get_instuction(t_list *list)
{
	t_list	*node;
	t_instruction	*inst;

	node = ft_lstlast(list);
	inst = (t_instruction*) node->content;
	return (inst);
}

void	ft_add_instruction(t_list **list)
{
	t_list	*node;
	t_instruction *inst;

	node = 0;
	inst = ft_init_instruction();
	if (inst)
		node = ft_lstnew(inst);
	if (node)
		ft_lstadd_back(list, node);
}
