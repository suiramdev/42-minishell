/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:11:36 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/27 00:18:22 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "builtins.h"
#include "libft.h"
#include <stdlib.h>

/// @brief Attempt to execute a builtin command
/// @param cmd The command to execute
/// @return EXIT_SUCCESS if the command was executed, EXIT_FAILURE otherwise
int	builtins(t_cmd *cmd)
{
	t_builtin	builtins[4];
	size_t	i;

	builtins[0] = (t_builtin){ .name = "echo", .func = builtin_echo };
	builtins[1] = (t_builtin){ .name = "env", .func = builtin_env };
	i = 0;
	while (builtins[i].name)
	{
		if (ft_strcmp(builtins[i].name, cmd->name) == 0)
		{
			builtins[i].func(cmd);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}
