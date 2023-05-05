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

/// @brief Skip quotes in a line
/// @param line The line to skip quotes from
/// @return The index of the next character after the quotes
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

/// @brief Check if the line contains pipes
/// @param str The line to check
/// @return 1 if the line contains pipes, 0 otherwise
int	has_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}
