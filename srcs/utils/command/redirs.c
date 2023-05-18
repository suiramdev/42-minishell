/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:51:58 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/17 16:23:50 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static bool	redir_heredoc(char *delimiter, t_cmd *cmd)
{
	char	*line;

	cmd->infile = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->infile < 0)
		return (perror("heredoc"), false);
	cmd->has_heredoc = 1;
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')", delimiter), false);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			return (free(line), false);
		ft_putendl_fd(line, cmd->infile);
		free(line);
	}
	return (true);
}

static bool	redir_output(char *filename, t_cmd *node, int append_flag)
{
	if (append_flag)
		node->outfile = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		node->outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->outfile < 0)
		return (perror("minishell"), false);
	return (true);
}

static bool	redir_input(char *filename, t_cmd *node)
{
	node->infile = open(filename, O_RDONLY);
	if (node->infile < 0)
		return (perror("minishell"), false);
	return (true);
}

/// @brief Initialize the redirections for the command
/// @param tokens The tokens array
/// @param i The index of the redirection token
/// @param node The command
/// @return true if the redirections were successfully initialized,
/// false otherwise
bool	init_redirs(char **tokens, size_t i, t_cmd *node)
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
	return (true);
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
