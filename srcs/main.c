/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:30:09 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/08 17:13:30 by mnouchet         ###   ########.fr       */
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
		add_env(&env, name, ft_strdup(getenv(name)));
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
	int		start;
	int		i;

	cmds = NULL;
	start = 0;
	i = 0;
	while (tokens[i])
	{
		if (has_pipes(tokens[i]))
		{
			new = new_cmd(tokens, start, i);
			add_cmd(&cmds, new);
			start = i + 1;
		}
		i++;
	}
	new = new_cmd(tokens, start, i);
	add_cmd(&cmds, new);
	return (cmds);
}

/// @brief Loop to read user input and execute commands
/// @param envs The environment variables linked list
/// @return EXIT_SUCCESS or EXIT_FAILURE if an error occured
static int	readentry(t_cmd **cmds, t_env *envs)
{
	char	*line;
	char	**tokens;
	int		exit_status;

	*cmds = NULL;
	while (1)
	{
		signal(SIGINT, &signal_handler);
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		tokens = tokenize(line);
		if (!tokens)
			return (free(line), EXIT_FAILURE);
		if (tokens[0])
			*cmds = init_cmds(tokens);
		exit_status = exec(*cmds, envs);
		free(line);
		free_tokens(tokens);
		free_cmds(*cmds);
		if (g_force_exit != -1)
			return (g_force_exit);
		if ((*cmds)->pid == 0)
			return (exit_status);
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
	exit_status = readentry(&cmds, envs);
	free_envs(envs);
	return (exit_status);
}
