/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:31:08 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/20 13:45:38 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Iterates over line to find the next token.
/// @param line Input string to parse.
/// @param quote Keeps track of the type of quotes (' or ") encountered.
/// @param i Index for iteration.
/// @return Returns true on successful parsing, false on encountering an error.
static bool	loop_get_next_token(char *line, char *quote, size_t *i)
{
	while (line[*i] && !is_space(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			if (!(*quote))
				(*quote) = line[*i];
			if (!handle_quotes(line, i))
				return (error("unclosed quotes ", 0), false);
		}
		else if ((line[*i] == '<' || line[*i] == '>'))
		{
			if ((*i) > 0 && !is_space(line[(*i) - 1]))
				break ;
			(*i)++;
			if (line[(*i)] == line[*i - 1])
				(*i)++;
			break ;
		}
		else if (line[*i] == ' ' || line[*i] == '|' || line[(*i) + 1] == '|')
			return ((*i)++, true);
		else
			(*i)++;
	}
	return (true);
}

/// @brief Get next token with space ' or " as delimiter
/// @param line_ptr The line's pointer to parse
/// @param envs The environment variables to replace by their values if 
/// double quotes
/// @return char* The next token
static char	*get_next_token(char **line, t_env *envs)
{
	char	*token;
	char	quote;
	size_t	i;

	i = 0;
	skip_spaces(*line, &i);
	*line += i;
	i = 0;
	quote = 0;
	if (!loop_get_next_token((*line), &quote, &i))
		return (NULL);
	token = ft_substr(*line, 0, i);
	if (quote)
		token = trim_token_quote(&token, quote, i, envs);
	skip_spaces(*line, &i);
	*line += i;
	return (token);
}

static int loop_count_tokens(char *line, size_t *i, size_t *count)
{
	if (line[(*i)] == '\'' || line[(*i)] == '"')
	{
		if (!handle_quotes(line, i))
			return (error("unclosed quotes ", 0), 0);
	}
	else if (line[(*i)] == '<' || line[(*i)] == '>')
	{
		if ((*i) > 0 && line[(*i) - 1] != ' ' && line != line + (*i))
			(*count)++;
		increase_token_index(count, i);
		if ((*i) > 0 && line[(*i) - 1] == line[(*i)])
			(*i)++;
		skip_spaces(line, i);
	}
	else if (line[(*i)] == ' ' || line[(*i)] == '|')
	{
		if (line[(*i)] == '|' && (*i) > 0 && line[(*i) - 1] != ' ' 
			&& line[(*i) - 1] != '<' && line[(*i) - 1] != '>' )
			(*count)++;
		increase_token_index(count, i);
		skip_spaces(line, i);
	}
	else
		(*i)++;
	return (1);
}

/// @brief Count the number of tokens in the input line
/// @param line The input line to count tokens in
/// @return The number of tokens in the line
static size_t	count_tokens(char *line)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	skip_spaces(line, &i);
	while (line[i])
	{
		if (!loop_count_tokens(line, &i, &count))
			return (0);
	}
	if (line[i] == '\0' && !is_space(line[i - 1]) && line[i - 1] != '<' && line[i - 1] != '>')
		count++;
	return (count);
}

/// @brief Tokenize a line
/// @param line The line to tokenize
/// @param envs The environment variables to consider during tokenization
/// @return An array of tokens
char	**tokenize(char *line, t_env *envs)
{
	size_t	i;
	size_t	tokens_count;
	char	**tokens;

	i = 0;
	tokens_count = count_tokens(line);
	printf("count: %ld\n", tokens_count);
	if (tokens_count <= 0)
		return (NULL);
	tokens = (char **)malloc(sizeof(char *) * (tokens_count + 1));
	if (!tokens)
		return (NULL);
	while (i < tokens_count)
		tokens[i++] = get_next_token(&line, envs);
	tokens[i] = NULL;
	return (tokens);
}