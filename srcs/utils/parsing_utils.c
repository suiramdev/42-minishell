#include "../../includes/minishell.h"

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void    free_tokens(char **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
        i++;

    while (i--)
        free(tokens[i]);
}

// Skip quotes ' or " to get token
int	skip_quotes(char *line)
{
	int		i;
	char	quote;

	i = 1;
	quote = line[0]; // ' or "
	while (line[i] && line[i] != quote)
			i++;
	if (line[i] == quote)
		return (i + 1);
	return (-1);
}
