/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:30:09 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/01 18:23:40 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/env.h"
#include "types/token.h"
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
static int	readentry(t_cmd *cmds, t_env *envs)
{
	char	*line;
	char	**tokens;

	cmds = 0;
	while (1)
	{
		// If ctrl+c signal, force loop again
		signal(SIGINT, &signal_handler);
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		tokens = tokenize(line);
		if (!tokens)
			return (free(line), free_tokens(tokens), EXIT_FAILURE);
		if (tokens[0])
			cmds = init_cmds(tokens);
		exec_cmds(cmds, envs);
		free(line);
		free_tokens(tokens);
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
	if (!readentry(&cmds, envs))
		return (EXIT_FAILURE);
	free_envs(envs);
	return (EXIT_SUCCESS);
}
