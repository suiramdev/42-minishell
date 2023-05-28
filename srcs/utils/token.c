/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:00:24 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/23 12:36:14 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Perform the second part of environment variable
/// replacement in a token string.
/// @param token The token string.
/// @param key_len The length of the key of the environment variable.
/// @param head A pointer to the environment variable list.
/// @param i The index in the token string where the replacement starts.
/// @return The updated token string after environment variable replacement.
static char	*replace_env_var2(char *token, int key_len, t_env *head, int i)
{
	char	*before;
	char	*after;
	char	*temp;

	before = ft_substr(token, 0, i);
	after = ft_strdup(token + i + key_len);
	temp = token;
	if (head)
	{
		token = ft_strjoin(before, head->value);
		free(before);
	}
	else
		token = before;
	free(temp);
	temp = token;
	token = ft_strjoin(token, after);
	free(temp);
	free(after);
	return (token);
}

static char	*replace_env_var_ext(char *token, int i, t_env *envs, bool *split_token)
{
	char	*key;
	size_t	key_len;

	key_len = 1;
	while (token[i + key_len] && !special_char(token[i + key_len]))
		key_len++;
	printf("keylen: %ld\n", key_len);
	if ((token[i + 1] >= '0' && token[i + 1] <= '9')
		|| token[i + 1] == '"' || token[i + 1] == '\'')
		key_len = 2;
	printf("keylen after: %ld\n", key_len);
	key = ft_substr(token, i + 1, key_len - 1);
	token = replace_env_var2(token, key_len, get_env(envs, key), i);
	free(key);
	if (ft_strchr(token, ' '))
		*split_token = true;
	return (token);
}

/// @brief Replace environment variables in a token string.
/// @param envs The environment variable list.
/// @param token The token string.
/// @return The updated token string after environment variable replacement.
char	*replace_env_var(t_env *envs, char *token, bool *split_token)
{
	size_t	i;
	char quote;

	i = 0;
	quote = 0;
	while (token[i])
	{
        if (!quote && (token[i] == '\'' || token[i] == '"'))
            quote = token[i++];
		else if (token[i] == quote)
			quote = 0;
		if (token[i] == '$' && quote != '\'')
		{
			if (token[i] == '$' && token[i + 1] && (token[i + 1] == '?'))
				token = replace_env_var2(token, 2, get_env(envs, "?"), i);
			else if (token[i + 1] && (!special_char(token[i + 1])
					|| token[i + 1] == '"' || token[i + 1] == '\''))
				token = replace_env_var_ext(token, i, envs, split_token);
			else
			{
				i++;
				continue ;
			}
			i = 0;
		}
		else
			i++;
	}
	return (token);
}

/// @brief Trim the quote characters from a token string
/// @param token The pointer to the token string.
/// @param quote The quote character to be trimmed.
/// @param len The length of the token string.
/// @param envs The environment variable list.
/// @return The updated token string after trimming and environment
/// variable replacement.
char	*trim_token_quote(char **token)
{
    char quote;
    char *str;
    size_t i;
	size_t str_index;

	str = (char*)malloc(sizeof(char) * strlen((*token)) + 1);
	if (!str)
		return (NULL);
	i = 0;
	str_index = 0;
	quote = '\0';
    while (i < ft_strlen((*token)))
    {
        if (!quote && ((*token)[i] == '\'' || (*token)[i] == '\"')) 
            quote = (*token)[i++];	// skip quote
		else if (quote && (*token)[i] == quote)
		{
			quote = '\0';
			i++; // skip quote
		}
        else 
            str[str_index++] = (*token)[i++];
    }
    str[str_index] = '\0';
    return (free(*token), str);
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
