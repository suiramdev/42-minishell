/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:31:08 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/08 20:58:25 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Get next token with space ' or " as delimiter
/// @param line_ptr The line's pointer to parse
/// @return char* The next token
static char	*get_next_token(char **line)
{
	size_t	i;
	char	quote;
	char	*token;

	while (is_space(*(*line)))
		(*line)++;
	i = 0;
	quote = '\0';
	if (is_quote((*line)[i]))
	{
		quote = *(*line);
		(*line)++;
		while ((*line)[i] && (*line)[i] != quote)
			i++;
	}
	else if ((*line)[i] == '|')
		i += 1 + (*line)[i + 1] == '|';
	else
	{
		while ((*line)[i] && !is_space((*line)[i])
			&& !is_quote((*line)[i]) && (*line)[i] != '|')
			i++;
	}
	token = ft_substr(*line, 0, i);
	if (!token)
		return (NULL);
    *line += i + (quote != '\0');
	return (token);
}

// Count the number of tokens in the line
static size_t	count_tokens(char *line)
{
	size_t	i;
	size_t	count;
	char	quote;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		if (is_quote(line[i]))
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] != quote)
				return (printf("error: quote not closed\n"), 0);
			count++;
			i++;
		}
		else if (line[i] == '|')
		{
			count++;
			if (line[i + 1] == '|')
				i++;
			if (line[i + 1] == '|')
				return (printf("error: syntax error near unexpected token `||\n"), 0);
			i++;
		}
		else if (line[i])
		{
			count++;
			while (line[i] && !is_space(line[i])
				&& !is_quote(line[i]) && line[i] != '|')
				i++;
		}
	}
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
