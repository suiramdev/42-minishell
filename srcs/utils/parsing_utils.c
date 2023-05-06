#include "../../includes/minishell.h"

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void    skip_spaces(char *line, int *i)
{
    while (is_space(line[(*i)]))
        (*i)++;
}

int	skip_quotes(char *line)
{
	int		i;
	char	quote;

	i = 1;
	quote = line[0];
	while (line[i] && line[i] != quote)
			i++;
	if (line[i] == quote)
		return (i + 1);
	return (-1);
}

int handle_quotes(char *line, int *i)
{
    int skip;

    skip = skip_quotes(line + (*i));
    if (skip == -1)
        return (0);
    (*i) += skip;
    return (1);
}

void    increase_token_index(int *count, int *i)
{
    (*count)++;
    (*i)++;
}
