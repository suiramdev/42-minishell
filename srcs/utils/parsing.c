/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:34:15 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/05 14:30:29 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @brief Check if the character is a space
/// @param c The character to check
/// @return 1 if the character is a space, 0 otherwise
int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

/// @brief Check if the character is a quote
/// @param c The character to check
/// @return 1 if the character is a quote, 0 otherwise
int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

/// @brief Check if the line contains pipes
/// @param str The line to check
/// @return 1 if the line contains pipes, 0 otherwise
int	has_pipes(char *str)
{
    int	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '"')
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}
