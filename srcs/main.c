/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:30:09 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/17 10:58:46 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_force_exit;

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
		set_env(&env, name, getenv(name));
		free(name);
		envp++;
	}
	return (env);
}

/// @brief Initialize the commands linked list from the tokens array
/// @param tokens The tokens array
/// @return The commands linked list
t_cmd	*init_cmds(char **tokens)
{
    t_cmd	*cmds;
    t_cmd	*new;
    size_t	start;
    size_t	i;

	cmds = NULL;
    start = 0;
    i = 0;
    while (tokens[i])
    {
        if (has_pipes(tokens[i]) && valid_last_command(tokens, i))
        {
            new = new_cmd(tokens, start, i);
            add_cmd(&cmds, new);
            start = i + 1;
        }
        i++;
    }
    if (tokens[start])
    {
        new = new_cmd(tokens, start, i);
        add_cmd(&cmds, new);
    }
    return (cmds);
}

/// @brief Loop to read user input and execute commands
/// @param cmds The commands linked list
/// @param envs The environment variables linked list
/// @return The exit status
static int	readentry(t_cmd **cmds, t_env **envs)
{
    char	*line;
    char	**tokens;
	int		exit_status;

    (void)envs;
    while (1)
    {
		signal(SIGINT, &signal_handler);
        line = readline("minishell$ ");
        if (!line)
            break;
        add_history(line);
        tokens = tokenize(line);
		free(line);
		if (!tokens)
			continue ;
		*cmds = init_cmds(tokens);
		free_tokens(tokens);
		if (*cmds)
		{
			if ((*cmds)->next)
				cmds_has_pipes(*cmds);
			exit_status = exec_cmds(*cmds, envs);
			if ((*cmds)->pid == 0)
			{
				free_cmds(*cmds);
				return (exit_status);
			}
			free_cmds(*cmds);
			if (g_force_exit != -1)
			    return (g_force_exit);
		}
    }
    return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envs;
	t_cmd	*cmds;
	int		exit_status;

	(void)argc;
	(void)argv;
	g_force_exit = -1;
	envs = init_envs(envp);
	exit_status = readentry(&cmds, &envs);
	free_envs(envs);
	return (exit_status);
}
