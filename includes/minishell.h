#ifndef MINISHELL_H

# define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>


// node struct in tree
typedef struct s_data {
    char **args;    // args[0]: echo  args[1]: -n args[x] = abc
    int infile; // for < <<
    int outfile; // for > >>
	// pid_t pid; // because each command is a process
    struct s_data *next;
}              t_data;

t_data *create_linked_list(char **tokens);

// redirection
int    handle_redirection(char **tokens, int i, t_data *node);
int    handle_heredoc(char *stop, t_data *node);

// parsing
int ft_loop(t_data *lst);

// utils
void signal_handler(int signal);
int	is_space(char c);
void    skip_spaces(char *line, int *i);
int	skip_quotes(char *line);
int handle_quotes(char *line, int *i);
void    increase_token_index(int *count, int *i);

// free
void    free_tokens(char **tokens);
void    free_nodes(t_data *head);

// list
t_data	*ft_listlast(t_data *lst);
void	ft_listadd_back(t_data **lst, t_data *new);
int valid_last_command(char **tokens, int i);


#endif
