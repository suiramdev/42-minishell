#include "../../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_data lst;

    (void)av;
    (void)ac;
    (void)envp;

	if (!isatty(STDIN_FILENO))
		return (printf("minishell: stdin is not a tty"), 0);
    if (!ft_loop(&lst))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
