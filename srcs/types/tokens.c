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
#include <stdio.h>

/// @brief Get next token with space ' or " as delimiter
/// @param line_ptr The line's pointer to parse
/// @return char* The next token
static char	*get_next_token(char **line)
{
	char	*token;
	size_t	start;
	size_t	end;

	start = 0;
	while (is_space((*line)[start]))
		start++;
	end = start;
	while (((*line)[end] && !is_space((*line)[end])))
	{
		if ((*line)[end] == '\'' || (*line)[end] == '"')
			end += skip_quotes(*line + end);
		else
			end++;
	}
	// Malloc token
	token = ft_substr(*line, start, end - start);
	if (!token)
		return (0);
	// Update line_ptr so we don't get same token over and over
	*line += end;
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
		return (NULL);
	// Put each token in tokens
	while (i < tokens_count)
		tokens[i++] = get_next_token(&line);
	tokens[i] = NULL;
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
