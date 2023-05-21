/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:34:15 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/17 16:20:06 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check if the character is a space
/// @param c The character to check
/// @return 1 if the character is a space, 0 otherwise
bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

/// @brief Skip all space characters in a line starting from a given index
/// @param line The line of text to process
/// @param i Pointer to the index in line from where to start skipping spaces
/// @return This function doesn't return a value. The index i is updated
/// in place to the next non-space character.
void	skip_spaces(char *line, size_t *i)
{
	while (is_space(line[(*i)]))
		(*i)++;
}

/// @brief Determine the length of a quoted string in a line, including
/// the quotes
/// @param line The line of text that starts with a quote
/// @return The length of the quoted string including the quotes.
/// If the closing quote is not found, returns -1.
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

/// @brief Handle quoted strings in a line starting from a given index
/// @param line The line of text to process
/// @param i Pointer to the index in line where the quoted string starts
/// @return 1 if a quoted string was successfully processed. 0 if the quoted
/// string was not correctly formatted (i.e., it was missing a closing quote).
bool	handle_quotes(char *line, size_t *i)
{
	int	skip;

	skip = skip_quotes(line + (*i));
	if (skip == -1)
		return (false);
	(*i) += skip;
	return (true);
}

/// @brief Increase a count variable and an index variable by one
/// @param count Pointer to the count variable to be increased
/// @param i Pointer to the index variable to be increased
/// @return This function doesn't return a value. Both count and i
/// are updated in place.
void	increase_token_index(size_t *count, size_t *i)
{
	(*count)++;
	(*i)++;
}
