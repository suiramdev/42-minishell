#include "../../includes/minishell.h"

void free_nodes(t_data *head)
{
    int i;
    t_data  *prev;

    i = 0;
    while (head)
    {
        if (head->infile > 2)
            close(head->infile);
        if (head->outfile > 2)
            close(head->outfile);
        while (head->args[i])
            free(head->args[i++]);
        if (head->args)
            free(head->args);
        prev = head;
        head = head->next;
        free(prev);
    }
}

void    free_tokens(char **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}