#include "../../includes/minishell.h"

// Handle ctrl+c signal
void signal_handler(int signal) 
{
    if (signal == SIGINT) {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}