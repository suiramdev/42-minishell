/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:29:53 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/08 18:47:16 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Read entry from stdin until the end of file,
/// and write it in the file descriptor fd.
/// @param eof The string that will stop the reading.
/// @return EXIT_SUCCESS or EXIT_FAILURE if an error occured.
static int	heredoc(char *eof, int fd)
{
    char	*line;

    while (1)
    {
		line = readline("> ");
		if (!line)
		{
			printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')", eof);
			return (EXIT_FAILURE);
		}
		if (ft_strcmp(line, eof) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
    }
	return (EXIT_SUCCESS);
}
