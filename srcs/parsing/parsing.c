#include "../../includes/minishell.h"

// Get next token with space ' or " as delimiter
static char	*get_next_token(char **line_ptr)
{
    char    *line = *line_ptr;
	char	*token;
	int		i;

	i = 0;

    // Skip leading spaces
    while (is_space(line[i]))
        i++;

    // While it's a character and not a white spice keep going
    while (line[i] && !is_space(line[i]))
	{
        // if it's a ' or ", skip it and keep going
		if (line[i] == '\'' || line[i] == '"')
			i += skip_quotes(line + i);
		else
			i++;
	}

    // Malloc token
	token = ft_substr(line, 0, i);
	if (!token)
		return (0);

    // Update line_ptr so we don't get same token over and over
    *line_ptr += i;

	return (token);
}

// Count the number of tokens in the line
static int count_token(char *line)
{
    int i;
    int tokens_count;

    i = 0;
    tokens_count = 0;

    while (line[i])
    {
		if (line[i] == '\'' || line[i] == '"')
			i += skip_quotes(line + i);
        else if (line[i] == ' ')
        {
            tokens_count++;
            i++;
        }
		else
			i++;
    }

    if (line[i] == '\0')
        tokens_count++;

    return (tokens_count);
}

// Tokenize the input line
static char    **parse_line(char *line)
{
    int i;
    int tokens_count;
    char **tokens;
    char *line_ptr;

    i = 0;
    tokens_count = count_token(line);

    // Allocate memory for tokens array
    tokens = (char **)malloc(sizeof(char *) * (tokens_count + 1));
    if (!tokens)
        return (0);

    line_ptr = line;
    // Put each token in tokens
    while (i < tokens_count)
        tokens[i++] = get_next_token(&line_ptr);
    tokens[i] = 0;

    return tokens;
}

int ft_loop(t_data *lst)
{
    char *line;
    char **tokens;
    t_data *head;

    lst = 0;
    while (1)
    {
        // If ctrl+c signal, force loop again
		signal(SIGINT, &signal_handler);

        // Print prompt and read user input
        line = readline("minishell$ ");
        
        // Handle ctrl+d
        if (!line)
            break;

        printf("-----\nline: %s\n-----\n", line);

        // Add history (can navigate with up/down arrow key)
        add_history(line);

        // Tokenize line to found tokens
        tokens = parse_line(line);
        if (!tokens)
            return (free(line), free_tokens(tokens), 0);

        // A delete c'est juste pour print les tokens
        int k = 0 ;
        while (tokens[k])
        {
            printf("tokens[%d]: %s\n", k, tokens[k]);
            k++;
        }

        // Separate commands in nodes with | as separator
        if (tokens[0])
            lst = create_linked_list(tokens);

        // A delete c'est juste pour print les nodes
        head = lst;
        int jj = 0;
        while (head)
        {
            for (int dd = 0; head->args[dd]; dd++)
                printf("node[%d]: args[%d]: %s\n", jj, dd, head->args[dd]);
            head = head->next;
            jj++;
        }

        free(line);
        free_tokens(tokens);
        // free_list(lst);
    }
    return (1);
}