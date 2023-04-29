#include "../../includes/minishell.h"

t_data	*ft_listlast(t_data *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_listadd_back(t_data **lst, t_data *new)
{
	t_data	*last;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		last = ft_listlast(*lst);
		last->next = new;
	}
}

t_data *create_node(char **tokens, int start, int end)
{
    t_data *node;
    int i;

    i = 0;

    node = (t_data *)malloc(sizeof(t_data));
    if (!node)
        return 0;

    node->args = (char **)malloc((end - start + 1) * sizeof(char *));
    if (!node->args)
        return 0;

    while (start + i < end)
    {
        node->args[i] = tokens[start + i];
        i++;
    }
        
    node->args[i] = 0;
    node->next = 0;

    return node;
}

t_data *create_linked_list(char **tokens)
{
    t_data *lst;
    t_data *new_node;
    int start;
    int i;

    lst = 0;
    start = 0;
    i = 0;
    while (tokens[i])
    {
        // If there is a pipe
        if (check_if_pipe(tokens[i]))
        {
            // Create a node with args[start] to args[i]
            new_node = create_node(tokens, start, i);
            ft_listadd_back(&lst, new_node);
            // Jump the pipe
            start = i + 1;
        }
        i++;
    }
    
    // Create node from 0 to end if no pipe
    // Or create last node from pipe to end if pipe
    new_node = create_node(tokens, start, i);
    ft_listadd_back(&lst, new_node);
    return lst;
}
