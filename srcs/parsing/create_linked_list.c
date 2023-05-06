#include "../../includes/minishell.h"

static int check_if_pipe(char *str)
{
    int i;

    i = 0;
    if (str[i] == '\'' || str[i] == '"')
        return (0);
    while (str[i])
    {
        if (str[i] == '|')
            return (1);
        i++;
    }
    return (0);
}

int node_init(t_data **node, int end, int start)
{
    (*node) = (t_data *)malloc(sizeof(t_data));
    if (!(*node))
        return (0);
    (*node)->infile = -1;
    (*node)->outfile = -1;
    (*node)->args = (char **)malloc((end - start + 1) * sizeof(char *));
    if (!(*node)->args)
        return (0);
    return (1);
}

t_data *create_node(char **tokens, int start, int end)
{
    t_data *node;
    int i;

    i = 0;
    if (!node_init(&node, end, start))
        return (NULL);
    while (start + i < end)
    {
        if ((tokens[start + i][0] == '>' || tokens[start + i][0] == '<')
            && node->infile == -1 && node->outfile == -1)
        {
            if (!handle_redirection(tokens, start + i, node))
                return (NULL);
            start += 2;
        }
        else
        {
            node->args[i] = tokens[start + i];
            i++;
        }
    }
    if (node->args[i - 1][0] == '|')
        i--;
    node->args[i] = NULL;
    node->next = NULL;

    return (node);
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
        if (check_if_pipe(tokens[i]) && valid_last_command(tokens, i))
        {
            new_node = create_node(tokens, start, i);
            if (new_node)
                ft_listadd_back(&lst, new_node);
            start = i + 1;
        }
        i++;
    }
    if (tokens[start])
    {
        new_node = create_node(tokens, start, i);
        ft_listadd_back(&lst, new_node);
    }
    return (lst);
}
