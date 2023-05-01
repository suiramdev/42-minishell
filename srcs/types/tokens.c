/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:31:08 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/01 16:42:57 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/parsing.h"
#include "libft.h"
#include <stdlib.h>

/// @brief Get next token with space ' or " as delimiter
/// @param line_ptr The line's pointer to parse
/// @return char* The next token
static char	*next_token(char **line)
{
	char	*token;
	int		i;

	i = 0;
	// Skip leading spaces
	while (is_space((*line)[i]))
		i++;
	// While it's a character and not a white spice keep going
	while (((*line)[i] && !is_space((*line)[i])))
	{
		// if it's a ' or ", skip it and keep going
		if ((*line)[i] == '\'' || (*line)[i] == '"')
			i += skip_quotes(*line + i);
		else
			i++;
	}
	// Malloc token
	token = ft_substr(*line, 0, i);
	if (!token)
		return (0);
	// Update line_ptr so we don't get same token over and over
	line += i;
	return (token);
}

// Count the number of tokens in the line
static int	count_token(char *line)
{
	int	i;
	int	tokens_count;

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

/// @brief Tokenize a line
/// @param line The line to tokenize
/// @return An array of tokens
char	**tokenize(char *line)
{
	int		i;
	int		tokens_count;
	char	**tokens;

	i = 0;
	tokens_count = count_token(line);
	// Allocate memory for tokens array
	tokens = (char **)malloc(sizeof(char *) * (tokens_count + 1));
	if (!tokens)
		return (0);
	// Put each token in tokens
	while (i < tokens_count)
		tokens[i++] = next_token(&line);
	tokens[i] = 0;
	return (tokens);
}

/// @brief Free tokens
/// @param tokens The tokens to free
void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	while (i--)
		free(tokens[i]);
}
