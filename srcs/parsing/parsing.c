#include "../../includes/minishell.h"

int token_loop(char *line, int *i)
{
    int skip;

    skip = 0;
	if (line[(*i)] == '\'' || line[(*i)] == '"')
    {
        skip = skip_quotes(line + (*i));
        if (skip == -1)
            return (0);
        (*i) += skip;
    }
    else if (line[(*i)] == ' ' || line[(*i)] == '|' || line[(*i) + 1] == '|')
    {
        (*i)++;
        return (2);
    }
    else
    {
        (*i)++;
    }
	return (1);
}

static char	*get_next_token(char **line_ptr)
{
    char    *line = *line_ptr;
	char	*token;
	int		i;
    int     res;

	i = 0;
    res = 0;
    skip_spaces(line, &i);
    while (line[i] && !is_space(line[i]))
	{
        res = token_loop(line, &i);
        if (!res)
            return (printf("error: quote not closed\n"), NULL);
        else if (res == 2)
            break;
	}
	token = ft_substr(line, 0, i);
	if (!token)
		return (0);
    skip_spaces(line, &i);
    *line_ptr += i;
	return (token);
}

static int count_token(char *line)
{
    int i;
    int tokens_count;

    i = 0;
    tokens_count = 0;
    skip_spaces(line, &i);
    while (line[i])
    {
		if (line[i] == '\'' || line[i] == '"')
        {
            if (!handle_quotes(line, &i))
                return (printf("error: quote not closed\n"), 0);
        }
        else if (line[i] == ' ' || line[i] == '|')
        {
            if (line[i] == '|' && line[i - 1] != ' ')
                increase_token_index(&tokens_count, &i);
            increase_token_index(&tokens_count, &i);
            skip_spaces(line, &i);
        }
		else
			i++;
    }
    if (line[i] == '\0' && !is_space(line[i - 1]))
        tokens_count++;
    return (tokens_count);
}

static char    **parse_line(char *line)
{
    int i;
    int tokens_count;
    char **tokens;
    char *line_ptr;

    i = 0;
    tokens_count = count_token(line);
    if (!tokens_count)
        return (0);
    tokens = (char **)malloc(sizeof(char *) * (tokens_count + 1));
    if (!tokens)
        return (0);
    line_ptr = line;
    while (i < tokens_count)
    {
        tokens[i] = get_next_token(&line_ptr);
        if (tokens[i] == 0)
            return (0);
        i++;
    }
    tokens[i] = NULL;
    return (tokens);
}

int ft_loop(t_data *lst)
{
    char *line;
    char **tokens;
    t_data *head;

    while (1)
    {
        line = NULL;
        tokens = NULL;
        lst = NULL;
		signal(SIGINT, &signal_handler);
        line = readline("minishell$ ");
        if (!line)
            break;
        add_history(line);
        tokens = parse_line(line);

        // A delete c'est juste pour print les tokens
        printf("-----\nline: %s\n-----\n", line);
        int k = 0 ;
        if (tokens)
        {
            while (tokens[k])
            {
                printf("tokens[%d]: %s\n", k, tokens[k]);
                k++;
            }
        }

        // Separate commands in nodes with | as separator
        if (tokens)
            lst = create_linked_list(tokens);

        // A delete c'est juste pour print les nodes
        if (lst)
        {
            head = lst;
            int jj = 0;
            while (head)
            {
                printf("node[%d]: infile: %d\toutfile: %d\n", jj, head->infile, head->outfile);
                for (int dd = 0; head->args[dd]; dd++)
                    printf("node[%d]: args[%d]: %s\n", jj, dd, head->args[dd]);
                head = head->next;
                jj++;
            }
        }

        // free(line);
        // if (tokens)
        //     free_tokens(tokens);
        // if (lst)
        //     free_nodes(lst);
    }
    return (EXIT_SUCCESS);
}