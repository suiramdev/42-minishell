/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:31:08 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/30 14:35:42 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Iterates over line to find the next token.
/// @param line Input string to parse.
/// @param quote Keeps track of the type of quotes (' or ") encountered.
/// @param i Index for iteration.
/// @return Returns true on successful parsing, false on encountering an error.
static bool	loop_get_next_token(char *line, int *quote, size_t *i)
{
	while (line[*i] && !is_space(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			*quote = 1;
			if (!handle_quotes(line, i))
				return (error("unclosed quotes ", 0), false);
			if (line[(*i)] == '|')
				return (true);
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
		else if (is_space(line[*i]) || line[*i] == '|' || line[(*i) + 1] == '|')
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
static char	*get_next_token(char **line, t_env *envs,
	bool *split_token, char *tokenpre)
{
	char	*token;
	int		quote;
	size_t	i;

	if (!*line)
		return (NULL);
	i = 0;
	skip_spaces(*line, &i);
	*line += i;
	i = 0;
	quote = 0;
	if (!loop_get_next_token((*line), &quote, &i))
		return (NULL);
	token = ft_substr(*line, 0, i);
	if (!token)
		return (NULL);
	if (ft_strchr(token, '$'))
		token = replace_env_var(envs, token, split_token, tokenpre);
	if (quote)
		token = trim_token_quote(&token);
	skip_spaces(*line, &i);
	*line += i;
	return (token);
}

static int	loop_count_tokens(char *line, size_t *i, size_t *count)
{
	if (line[(*i)] == '\'' || line[(*i)] == '"')
	{
		if (!handle_quotes(line, i))
			return (error("unclosed quotes ", 0), 0);
	}
	else if (line[(*i)] == '<' || line[(*i)] == '>')
	{
		if ((*i) > 0 && !is_space(line[(*i) - 1]) && line != line + (*i))
			(*count)++;
		increase_token_index(count, i);
		if ((*i) > 0 && line[(*i) - 1] == line[(*i)])
			(*i)++;
		skip_spaces(line, i);
	}
	else if (is_space(line[(*i)]) || line[(*i)] == '|')
	{
		if (line[(*i)] == '|' && (*i) > 0 && !is_space(line[(*i) - 1])
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
	if ((line[i] == '\0' && !is_space(line[i - 1]) && line[i - 1] != '<'
			&& line[i - 1] != '>')
		|| (check_end_by_quote(line, i) && count == 0))
		count++;
	return (count);
}

/// @brief Tokenize a line
/// @param line The line to tokenize
/// @param envs The environment variables to consider during tokenization
/// @return An array of tokens
char	**tokenize(char *line, t_env *envs, char *pretoken)
{
	size_t	i;
	size_t	j;
	size_t	tokens_count;
	char	**tokens;
	bool	split_token;

	split_token = false;
	i = 0;
	j = 0;
	tokens_count = count_tokens(line);
	if (tokens_count <= 0)
		return (NULL);
	tokens = (char **)malloc(sizeof(char *) * (tokens_count + 1));
	if (!tokens)
		return (NULL);
	while (i++ < tokens_count)
	{
		tokens[j++] = get_next_token(&line, envs, &split_token, pretoken);
		if (split_token)
			tokens = token_split(tokens, &j, &split_token, tokens_count);
		pretoken = tokens[j - 1];
	}
	tokens[j] = NULL;
	return (handle_unexpected(&tokens), tokens);
}
