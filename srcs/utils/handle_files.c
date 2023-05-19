/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:29:53 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/09 16:09:22 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Read entry from stdin until the end of file,
/// and write it in the file descriptor fd.
/// @param delimiter The string that will stop the reading.
/// @param node The command node where the infile field is updated 
/// with the file descriptor of a temporary file containing the input data.
/// @return EXIT_SUCCESS or EXIT_FAILURE if an error occured.
static int	handle_heredoc(char *delimiter, t_cmd *node)
{
    char	*line;

	node->infile = open("heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->infile < 0)
		return (ft_errorendl("heredoc", strerror(errno)), 0);
	node->has_heredoc = 1;
    while (1)
    {
		line = readline("> ");
		if (!line)
			return (heredoc_error(delimiter), EXIT_FAILURE);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			return (free(line), EXIT_SUCCESS);
		ft_putendl_fd(line, node->infile);
		free(line);
    }
	return (EXIT_SUCCESS);
}

/// @brief Handle output redirection in shell command to a file. 
/// It can either append to the file or overwrite it.
/// @param filename The name of the file to which the output will be redirected.
/// @param node The command node where the outfile field is updated with the file descriptor of the output file.
/// @param append_flag A flag that specifies whether to append to the file (1) or overwrite it (0).
/// @return 1 if the output redirection was successful, or 0 if an error occurred.
static int    handle_output(char *filename, t_cmd *node, int append_flag)
{
	if (append_flag)
		node->outfile = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		node->outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->outfile < 0)
		return (ft_errorendl(filename, strerror(errno)), 0);
	return (1);
}

/// @brief Handle input redirection in shell command from a file.
/// @param filename The name of the file from which the input will be redirected.
/// @param node The command node where the infile field is updated with the file descriptor of the input file.
/// @return 1 if the input redirection was successful, or 0 if an error occurred.
static int    handle_input(char *filename, t_cmd *node)
{
	node->infile = open(filename, O_RDONLY);
	if (node->infile < 0)
		return (ft_errorendl(filename, strerror(errno)), 0);
	return (1);
}

/// @brief Process redirection operations ('>', '>>', '<', '<<') in shell command.
/// @param tokens The array of command tokens.
/// @param i The index of the redirection operator in the tokens array.
/// @param node The command node where the infile and outfile fields are updated based on the redirection operations.
/// @return 1 if the redirection handling was successful, or 0 if an error occurred.
int    handle_redirection(char **tokens, int i, t_cmd *node)
{
	int	r;

	r = 1;
    if (tokens[i][0] == '>')
	{
		if (node->outfile > 2)
			close(node->outfile);
		if (tokens[i][1] == '>')
        	r = handle_output(tokens[i + 1], node, 1);
		else
        	r = handle_output(tokens[i + 1], node, 0);
	}
    else if (tokens[i][0] == '<')
	{
		if (node->infile > 2)
			close(node->outfile);
		if (tokens[i][1] == '<')
        	r = handle_heredoc(tokens[i + 1], node);
		else
			r = handle_input(tokens[i + 1], node);
	}
	return (r);
}