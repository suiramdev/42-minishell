#include "../../includes/minishell.h"

static int	is_file_writable(char *filename)
{
	if (access(filename, F_OK) != 0)
		return (1);
    if (access(filename, W_OK) == 0)
        return (1);
    else
        return (printf("write permission denied"), 0);
}

static int	is_file_readable(char *filename)
{
    if (access(filename, R_OK) == 0)
        return 1;
    else
        return (printf("read permission denied"), 0);
}

static int    handle_output(char *filename, t_data *node, int append_flag)
{
	if (!is_file_writable(filename))
		return (node->infile = -1, 0);
	if (append_flag)
		node->outfile = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		node->outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->outfile < 0)
		return (printf("%s: No such file or directory", filename), 0);
	return (1);
}

static int    handle_input(char *filename, t_data *node)
{
	if (!is_file_readable(filename))
		return (node->infile = -1, 0);
	node->infile = open(filename, O_RDONLY);
	if (node->infile < 0)
		return (printf("%s: No such file or directory", filename), 0);
	return (1);
}

int    handle_redirection(char **tokens, int i, t_data *node)
{
	int	r;

	r = 1;
    if (tokens[i][0] == '>')
	{
		if (tokens[i][1] == '>')
        	r = handle_output(tokens[i + 1], node, 1);
		else
        	r = handle_output(tokens[i + 1], node, 0);
	}
    else if (tokens[i][0] == '<')
	{
		if (tokens[i][1] == '<')
        	r = handle_heredoc(tokens[i + 1], node);
		else
			r = handle_input(tokens[i + 1], node);
	}
	return (r);
}
