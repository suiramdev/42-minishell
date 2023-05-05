/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:31 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/05 14:54:58 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include <stdlib.h>
#include <stdio.h>

/// @brief Execute the env builtin command
/// @param cmd The command data structure
/// @param envs The environment variables
int	builtin_env(t_cmd *cmd, t_env *envs)
{
	char	**formatted_env;
	size_t	i;

	(void)cmd;
	formatted_env = format_env(envs);
	i = 0;
	while (formatted_env[i])
	{
		printf("%s\n", formatted_env[i]);
		free(formatted_env[i++]);
	}
	free(formatted_env);
	return (EXIT_SUCCESS);
}
