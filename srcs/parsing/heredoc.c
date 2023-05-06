#include "../../includes/minishell.h"

static int read_line(char *stop, char **str)
{
    char *line;

    line = readline("> ");
    if (!line)
        return (printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')", stop), 0);
    if (strncmp(line, stop, ft_strlen(stop)) == 0)
        return (free(line), 0);
    *str = ft_substr(line, 0, ft_strlen(line));
    free(line);
    if (!*str)
        return (0);
    return (1);
}

static int read_heredoc(char *stop, int fd)
{
    char *line;
    int r;

    while (1)
    {
        line = NULL;
        r = read_line(stop, &line);
        if (!r)
            break;

        if (line)
        {
            ft_putendl_fd(line, fd);
            free(line);
        }
    }
    if (line)
        free(line);
    return (r);
}


int handle_heredoc(char *stop, t_data *node)
{
    if (!stop || !read_heredoc(stop, node->outfile))
        return (0);
    return (1);
}