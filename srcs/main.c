/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:30:09 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/27 00:24:11 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/env.h"
#include "types/command.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

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
		add_env(&env, name, getenv(name));
		envp++;
	}
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envs;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	envs = init_envs(envp);
	cmds = example_cmds(envs);
	exec_cmds(cmds);
	free_envs(envs);
	return (EXIT_SUCCESS);
}
