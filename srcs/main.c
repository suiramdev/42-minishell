/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:30:09 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/29 17:03:35 by zdevove          ###   ########.fr       */
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
		set_env(&env, name, ft_strdup(getenv(name)));
		free(name);
		envp++;
	}
	set_env(&env, "?", ft_strdup("0"));
	return (env);
}

/// @brief Initialize the commands linked list from the tokens array
/// @param tokens The tokens array
/// @return The commands linked list
static t_cmd	*init_cmds(char **tokens)
{
	t_cmd	*cmds;
	size_t	start;
	size_t	i;

	cmds = NULL;
	start = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
		{
			add_cmd(&cmds, new_cmd(tokens, start, i));
			start = i + 1;
		}
		i++;
	}
	if (tokens[start])
		add_cmd(&cmds, new_cmd(tokens, start, i));
	if (cmds && cmds->next)
		cmds_has_pipes(cmds);
	return (cmds);
}

/// @brief Read user input, tokenize it and initialize the commands linked list
/// @param envs The environment variables linked list
/// @param cmds The commands linked list
static int	readentry(t_env **envs, t_cmd **cmds)
{
	char	*line;
	char	**tokens;

	line = readline("minishell# ");
	if (!line)
		return (2);
	add_history(line);
	if (line[0] == '\0')
		return (free(line), 0);
	tokens = tokenize(line, *envs);
	free(line);
	if (!tokens)
	{
		set_env(envs, "?", ft_strdup("2"));
		return (0);
	}
	*cmds = init_cmds(tokens);
	free_tokens(tokens);
	return (1);
}

/// @brief Loop to read user input and execute commands
/// @param cmds The commands linked list
/// @param envs The environment variables linked list
/// @return The exit status
static int	program(t_cmd **cmds, t_env **envs)
{
	int		exit_status;
	int		res;

	while (1)
	{
		signal(SIGINT, &main_signal);
		signal(SIGQUIT, SIG_IGN);
		res = readentry(envs, cmds);
		if (res == 2)
			break ;
		else if (res == 0)
			continue ;
		if (*cmds)
		{
			set_env(envs, "_", ft_strdup(last_cmd_arg(*cmds)));
			int k = 0;
			for (t_cmd *head = *cmds; head; head = head->next)
			{
				for (int i = 0; head->args[i]; i++)
					printf("node[%d]: args[%d]: %s\n", k, i, head->args[i]);
				k++;
			}
			exit_status = exec_cmds(*cmds, envs);
			if (is_child_process(*cmds))
				return (free_cmds(*cmds), exit_status);
			free_cmds(*cmds);
		}
		if (g_force_exit != -1)
			return (g_force_exit);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envs;
	t_cmd	*cmds;
	int		exit_status;
	t_env	*tmp;

	(void)argc;
	(void)argv;
	cmds = NULL;
	g_force_exit = -1;
	envs = init_envs(envp);
	exit_status = program(&cmds, &envs);
	rl_clear_history();
	while (envs)
	{
		tmp = envs;
		envs = envs->next;
		free_env(tmp);
	}
	return (exit_status);
}
