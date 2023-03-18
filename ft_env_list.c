void    ft_add2list(t_list **list, t_list *n_elm)
{
    if (!*list)
	{
		*list = n_elm;
		return ;
	}
    if (!n_elm)
        return ;
    n_elm->next = *list;
    *list = n_elm;
}

t_list  *create_elm(char *key, char *val)
{
    t_list  *new_lst;

    new_lst = (t_list *) malloc(sizeof(t_list));
    if (!new_lst)
        return (NULL);
    if (!key || !val)
        return (NULL);
    new_lst->key = ft_strdup(key);
    if (!new_lst->key)
        return (NULL);
    new_lst->val = ft_strdup(val);
    if (!new_lst->val)
        return (NULL);
    new_lst->next = NULL;
    return (new_lst);
}

char    *ft_find_elm(t_list **list, char *key)
{
    t_list  *tmp;

    if (!list || !*list)
        return (NULL);
    tmp = *list;
    while (tmp->next != NULL)
    {
        if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
            return (ft_strdup(tmp->val));
        tmp = tmp->next;
    }
    return (NULL);
}

void    ft_del_node(t_list *elm)
{
    if (!elm)
        return ;
    if (elm->key)
        free(elm->key);
    if (elm->val)
        free (elm->val);
    free(elm);
}

void    ft_delete_elm(t_list **list, char *key)
{
    t_list  *head;
    t_list  *tmp;

    if (!list || !*list || !key)
    {
        printf("err: no list or key is null\n");
        return;
    }
    head = *list;
    tmp = *list;
    if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key)) == 0) //1st elm del
    {
        ft_del_node(*list);
        // free(*list);
        *list = tmp->next;
        return ;
    }
    tmp = (*list)->next;
    while (ft_strncmp(tmp->key, key, ft_strlen(tmp->key)) && (*list)->next != NULL)
    {
        *list = (*list)->next;
        tmp = tmp->next;
    }
    ft_del_node((*list)->next);
    // free((*list)->next);
    (*list)->next = tmp->next;
    *list = head;
}
