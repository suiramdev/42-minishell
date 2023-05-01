/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:30:09 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/01 16:55:40 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/env.h"
#include "types/tokens.h"
#include "types/command.h"
#include "utils/signal.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

/// @brief Initialize the environment variables from the envp array
/// @param envp The environment variables array
/// @return The environment variables linked list
static t_env	*init_envs(char **envp)
{
	t_env	*env;
	char	*name;
	size_t	i;

	env = NULL;
	while (*envp)
	{
		i = 0;
		while ((*envp)[i] != '=')
			i++;
		name = ft_substr(*envp, 0, i);
		add_env(&env, name, ft_strdup(getenv(name)));
		envp++;
	}
	return (env);
}

/// @brief Loop to read user input and execute commands
/// @param envs The environment variables linked list
/// @return The exit status
static int	readentry(t_cmd *cmds)
{
    char	*line;
    char	**tokens;
    t_cmd	*head;

    cmds = 0;
    while (1)
    {
        // If ctrl+c signal, force loop again
		signal(SIGINT, &signal_handler);
        // Print prompt and read user input
        line = readline("minishell$ ");
        // Handle ctrl+d
        if (!line)
            break;
        printf("-----\nline: %s\n-----\n", line);
        // Add history (can navigate with up/down arrow key)
        add_history(line);
        // Tokenize line to found tokens
        tokens = tokenize(line);
        if (!tokens)
            return (free(line), free_tokens(tokens), EXIT_FAILURE);
        // A delete c'est juste pour print les tokens
        int k = 0 ;
        while (tokens[k])
        {
            printf("tokens[%d]: %s\n", k, tokens[k]);
            k++;
        }
        // Separate commands in nodes with | as separator
        if (tokens[0])
            cmds = init_cmds(tokens);
        // A delete c'est juste pour print les nodes
        head = cmds;
        int jj = 0;
        while (head)
        {
            for (int dd = 0; head->args[dd]; dd++)
                printf("node[%d]: args[%d]: %s\n", jj, dd, head->args[dd]);
            head = head->next;
            jj++;
        }
        free(line);
        free_tokens(tokens);
        // free_list(lst);
    }
    return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envs;
	t_cmd	cmds;

	(void)argc;
	(void)argv;
	envs = init_envs(envp);
	if (!readentry(&cmds))
        return (0);
	free_envs(envs);
	return (EXIT_SUCCESS);
}
