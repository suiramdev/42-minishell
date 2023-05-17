/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:51:58 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/17 10:03:53 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	redir_heredoc(char *delimiter, t_cmd *cmd)
{
    char	*line;

	cmd->infile = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->infile < 0)
		return (perror("heredoc"), EXIT_FAILURE);
	cmd->has_heredoc = 1;
    while (1)
    {
		line = readline("> ");
		if (!line)
			return (printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')", delimiter), EXIT_FAILURE);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			return (free(line), EXIT_SUCCESS);
		ft_putendl_fd(line, cmd->infile);
		free(line);
    }
	return (EXIT_SUCCESS);
}

static int    redir_output(char *filename, t_cmd *node, int append_flag)
{
	if (append_flag)
		node->outfile = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		node->outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->outfile < 0)
		return (perror("minishell"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int    redir_input(char *filename, t_cmd *node)
{
	node->infile = open(filename, O_RDONLY);
	if (node->infile < 0)
		return (perror("minishell"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/// @brief Initialize the redirections for the command
/// @param tokens The tokens array
/// @param i The index of the redirection token
/// @param node The command
/// @return EXIT_SUCCESS or EXIT_FAILURE if an error occured.
int	init_redirs(char **tokens, int i, t_cmd *node)
{
    if (tokens[i][0] == '>')
	{
		if (node->outfile > 2)
			close(node->outfile);
		return (redir_output(tokens[i + 1], node, tokens[i][1] == '>'));
	}
    else if (tokens[i][0] == '<')
	{
		if (node->infile > 2)
			close(node->outfile);
		if (tokens[i][1] == '<')
        	return (redir_heredoc(tokens[i + 1], node));
		return (redir_input(tokens[i + 1], node));
	}
	return (EXIT_SUCCESS);
}

/// @brief Redirect the input and output of the command
/// @param cmd The command
void	redirs(t_cmd *cmd)
{
	if (cmd->infile > 0)
		dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile > 0)
		dup2(cmd->outfile, STDOUT_FILENO);
}

void	close_redirs(t_cmd *cmd)
{
	if (cmd->infile > 0)
		close(cmd->infile);
	if (cmd->outfile > 0)
		close(cmd->outfile);
	if (cmd->has_heredoc)
		unlink(HEREDOC_FILE);
}
