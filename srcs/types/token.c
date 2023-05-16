/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:31:08 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/09 16:11:19 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Get next token with space ' or " as delimiter
/// @param line_ptr The line's pointer to parse
/// @return char* The next token
static char	*get_next_token(char **line)
{
	char	*token;
	size_t	i;
	int		skip;

	i = 0;
    skip_spaces(*line, &i);
    *line += i;
    while ((*line)[i] && !is_space((*line)[i]))
	{
		skip = 0;
		if ((*line)[i] == '\'' || (*line)[i] == '"')
		{
			skip = skip_quotes(*line + i);
			if (skip == -1)
				return (printf("error: quote not closed\n"), NULL);
			i += skip;
            break ;
		}
		else if ((*line)[i] == ' ' || (*line)[i] == '|' || (*line)[i + 1] == '|')
		{
			i++;
			break ;
		}
		else
			i++;
	}
	token = ft_substr(*line, 0, i);
	if (!token)
		return (0);
    skip_spaces(*line, &i);
    *line += i;
	return (token);
}

// Count the number of tokens in the line
static size_t	count_tokens(char *line)
{
    size_t	i;
    size_t	count;

    i = 0;
    count = 0;
    skip_spaces(line, &i);
    while (line[i])
    {
		if (line[i] == '\'' || line[i] == '"')
        {
            if (!handle_quotes(line, &i))
                return (printf("error: quote not closed\n"), 0);
            count++;
        }
		else if (line[i] == ' ' || line[i] == '|')
        {
            if (line[i] == '|' && line[i - 1] != ' ')
                increase_token_index(&count, &i);
            increase_token_index(&count, &i);
            skip_spaces(line, &i);
        }
		else
			i++;
    }
    if (line[i] == '\0' && !is_space(line[i - 1]) && line[i - 1] != '\'' && line[i - 1] != '"')
        count++;
    return (count);
}

/// @brief Tokenize a line
/// @param line The line to tokenize
/// @return An array of tokens
char	**tokenize(char *line) {
    size_t	i;
    size_t	tokens_count;
    char	**tokens;

    i = 0;
    tokens_count = count_tokens(line);
    printf("tokens count: %ld\n", tokens_count);
    if (tokens_count <= 0)
        return (NULL);
    tokens = (char **)malloc(sizeof(char *) * (tokens_count + 1));
    if (!tokens)
        return (NULL);
    while (i < tokens_count)
        tokens[i++] = get_next_token(&line);
    tokens[i] = NULL;
    return (tokens);
}

/// @brief Free tokens
/// @param tokens The tokens to free
void	free_tokens(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
