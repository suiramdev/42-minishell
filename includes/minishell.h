#ifndef MINISHELL_H

# define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>


// node struct in tree
typedef struct s_data {
    // char *cmd; // command type: echo, cd, pipe, etc.
    // char *line;
    char **args;    // args[0]: echo  args[1]: -n args[x] = abc
                    // args[0]: cd  args[1]: path
    // char *options;  // -n
    // char *path;
    // int infile; // for < <<
    // int outfile; // for > >>
	// pid_t pid; // because each command is a process
    struct s_data *next;
}              t_data;

t_data *create_linked_list(char **tokens);

// parsing
int ft_loop(t_data *lst);

// utils
int check_if_pipe(char *str);
void signal_handler(int signal);
void free_tokens(char **tokens);
int	is_space(char c);
int	skip_quotes(char *line);

#endif
