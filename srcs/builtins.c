/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:11:36 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/01 18:23:04 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "builtins.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

/// @brief Attempt to execute a builtin command
/// @param cmd The command to execute
/// @param envs The environment variables
/// @return EXIT_SUCCESS if the command was executed, EXIT_FAILURE otherwise
int	builtins(t_cmd *cmd, t_env *envs)
{
	t_builtin	builtins[5];
	size_t		i;

	builtins[0] = (t_builtin){.name = "cd", .func = builtin_cd};
	builtins[1] = (t_builtin){.name = "echo", .func = builtin_echo};
	builtins[2] = (t_builtin){.name = "env", .func = builtin_env};
	builtins[3] = (t_builtin){.name = "exit", .func = builtin_exit};
	builtins[4] = (t_builtin){.name = "pwd", .func = builtin_pwd};
	i = 0;
	while (i < 5)
	{
		if (ft_strcmp(builtins[i].name, cmd->name) == 0)
		{
			builtins[i].func(cmd, envs);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}
