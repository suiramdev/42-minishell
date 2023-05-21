/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:30:09 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/19 15:36:38 by mnouchet         ###   ########.fr       */
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
	size_t	start;
	size_t	i;

	cmds = NULL;
	start = 0;
	i = 0;
	while (tokens[i])
	{
		if (has_pipes(tokens[i]) && valid_last_command(tokens, i))
		{
			add_cmd(&cmds, new_cmd(tokens, start, i));
			start = i + 1;
		}
		i++;
	}
	if (tokens[start])
		add_cmd(&cmds, new_cmd(tokens, start, i));
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

	while (1)
	{
		signal(SIGINT, &signal_handler);
		line = readline("minishell$ ");
		if (!line)
			return (EXIT_FAILURE);
		add_history(line);
		tokens = tokenize(line, *envs);
		free(line);
		if (!tokens)
			continue ;

        // A delete c'est juste pour print les tokens
		// print line
		// print tokens
        if (tokens)
			for (int k = 0; tokens[k]; k++)
                printf("tokens[%d]: %s\n", k, tokens[k]);
		*cmds = init_cmds(tokens);
		free_tokens(tokens);
		if (*cmds)
		{
	        // A delete c'est juste pour print les nodes
			// print nodes
			t_cmd *head;
            head = *cmds;
            int jj = 0;
            while (head)
            {
                printf("node[%d]: infile: %d\toutfile: %d\n", jj, head->infile, head->outfile);
                for (int dd = 0; head->args[dd]; dd++)
                    printf("node[%d]: args[%d]: %s\n", jj, dd, head->args[dd]);
                head = head->next;
                jj++;
            }
			if ((*cmds)->next)
				cmds_has_pipes(*cmds);
			exit_status = exec_cmds(*cmds, envs);
			if ((*cmds)->pid == 0)
				return (free_cmds(*cmds), exit_status);
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
	t_env	*tmp;

	(void)argc;
	(void)argv;
	cmds = NULL;
	g_force_exit = -1;
	envs = init_envs(envp);
	exit_status = readentry(&cmds, &envs);
	rl_clear_history();
	while (envs)
	{
		tmp = envs;
		envs = envs->next;
		free_env(tmp);
	}
	return (exit_status);
}
