/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:30:09 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/26 17:06:25 by mnouchet         ###   ########.fr       */
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
static t_env	*init_env(char **envp)
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
	t_env	*env;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	cmd = example_cmd(env);
	exec_cmd(cmd);
	return (EXIT_SUCCESS);
}
