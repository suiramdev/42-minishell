#include "../../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_data lst;

    (void)av;
    (void)ac;
    (void)envp;

    if (!ft_loop(&lst))
        return (0);

    return (0);
}
