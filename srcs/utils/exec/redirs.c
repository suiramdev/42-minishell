/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:51:58 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/26 02:01:43 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Close and open back the file descriptor of the heredoc file.
/// @param cmd The command node where the infile field will be updated.
static void	reopen_heredoc(t_cmd *cmd)
{
	close(cmd->infile);
	cmd->infile = open(HEREDOC_FILE, O_RDONLY);
}

/// @brief Read entry from stdin until the end of file,
/// and write it in the file descriptor fd.
/// @param delimiter The string that will stop the reading.
/// @param node The command node where the infile field is updated 
/// with the file descriptor of a temporary file containing the input data.
/// @return EXIT_SUCCESS or EXIT_FAILURE if an error occured.
static bool	redir_heredoc(char *delimiter, t_cmd *cmd)
{
	char	*line;

	cmd->infile = open(HEREDOC_FILE, O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if (cmd->infile < 0)
		return (error("heredoc", strerror(errno)), false);
	cmd->has_heredoc = true;
	while (1)
	{
		signal(SIGINT, &heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
		rl_getc_function = getc;
		line = readline("> ");
		if (!line)
			return (reopen_heredoc(cmd), error_heredoc(delimiter), true);
		if (ft_strcmp(line, delimiter) == 0)
			return (reopen_heredoc(cmd), free(line), true);
		ft_putendl_fd(line, cmd->infile);
		free(line);
	}
	return (true);
}

/// @brief Process redirection operations ('>', '>>', '<', '<<')
/// in shell command.
/// @param tokens The array of command tokens.
/// @param i The index of the redirection operator in the tokens array.
/// @param node The command node where the infile and outfile fields
/// are updated based on the redirection operations.
/// @return true if the redirection handling was successful, or false
/// if an error occurred.
bool	init_redirs(char **tokens, size_t i, t_cmd *cmd)
{
	if (tokens[i][0] == '>')
	{
		if (cmd->outfile > 2)
			close(cmd->outfile);
		if (tokens[i][1] == '>')
			cmd->outfile = open(tokens[i + 1], O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		else
			cmd->outfile = open(tokens[i + 1], O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		if (cmd->outfile < 0)
			return (perror("minishell"), false);
	}
	else if (tokens[i][0] == '<')
	{
		if (cmd->infile > 2)
			close(cmd->infile);
		if (tokens[i][1] == '<')
			return (redir_heredoc(tokens[i + 1], cmd));
		cmd->infile = open(tokens[i + 1], O_RDONLY);
		if (cmd->infile < 0)
			return (perror("minishell"), false);
	}
	return (true);
}

/// @brief Redirect the input and output of the command
/// on STDIN and STDOUT.
/// @param cmd The command
void	redirs(t_cmd *cmd)
{
	if (cmd->infile > 0)
		dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile > 0)
		dup2(cmd->outfile, STDOUT_FILENO);
}

/// @brief Close the input and output redirections of the command
/// and delete the temporary file containing the heredoc input.
/// @param cmd The command
void	close_redirs(t_cmd *cmd)
{
	if (cmd->infile > 2)
		close(cmd->infile);
	if (cmd->outfile > 2)
		close(cmd->outfile);
	if (cmd->has_heredoc)
		unlink(HEREDOC_FILE);
}
