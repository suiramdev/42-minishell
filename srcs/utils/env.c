#include "minishell.h"

/// @brief Check if a command token string contains any special characters.
/// @param c The character to check.
/// @return 1 if the character is special, 0 otherwise.
static int special_char(char c)
{
    return !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || 
             (c >= '0' && c <= '9') || (c == '_'));
}

/// @brief Perform the second part of environment variable replacement in a token string.
/// @param token The token string.
/// @param key_len The length of the key of the environment variable.
/// @param head A pointer to the environment variable list.
/// @param i The index in the token string where the replacement starts.
/// @return The updated token string after environment variable replacement.
static char    *replace_env_var2(char *token, int key_len, t_env *head, int i)
{
	char    *before;
    char    *after;
    char    *temp;

    before = ft_substr(token, 0, i);
    after = ft_strdup(token + i + key_len);
    temp = token;
	if (head)
            token = ft_strjoin(before, head->value);
	else
			token = before;
	free(temp);
	temp = token;
    token = ft_strjoin(token, after);
    // free(temp);
	if (before)
    	free(before);
    free(after);
	return (token);
}

/// @brief Replace environment variables in a token string.
/// @param envs The environment variable list.
/// @param token The token string.
/// @return The updated token string after environment variable replacement.
static char    *replace_env_var(t_env *envs, char *token)
{
    t_env   *head;
    size_t  i;
    size_t  key_len;
    char    *key;

    i = 0;
    while (token[++i])
    {
        if (token[i] == '$')
        {
            key_len = 1;
            while (!special_char(token[i + key_len]))
                key_len++;
            key = ft_substr(token, i + 1, key_len - 1);
            head = envs;
            while (head && ft_strncmp(key, head->key, ft_strlen(key)) != 0)
            	head = head->next;
			token = replace_env_var2(token, key_len, head, i);
            free(key);
        }
    }
    return (token);
}

/// @brief Trim the quote characters from a token string and handle environment variable replacement if necessary.
/// @param token The pointer to the token string.
/// @param quote The quote character to be trimmed.
/// @param len The length of the token string.
/// @param envs The environment variable list.
/// @return The updated token string after trimming and environment variable replacement.
char 	*trim_token_quote(char **token, char quote, int len, t_env *envs)
{
	int i;
	int j;
	char *src;
	char *dst;

	i = 0;
	j = 0;
	src = *token;
	while (src[i])
		if (src[i++] == quote)
			j++;
	dst = malloc((len - j + 3) * sizeof(char));
	if (!dst)
		return (0);
	i = -1;
	j = 1;
	dst[0] = quote;
	while (++i < len)
		if (src[i] != quote)
			dst[j++] = src[i];
	dst[j++] = quote;
	dst[j] = '\0';
	free(*token);
	if (quote == '"' && ft_strchr(dst, '$'))
		return (replace_env_var(envs, dst));
	return (dst);
}
