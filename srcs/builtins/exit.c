/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:39 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/08 17:19:20 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Execute the exit builtin command
/// @param cmd The command to execute
/// @param envs The environment variables
/// @return The exit status
/// @note Should be executed in the main process
int	builtin_exit(t_cmd *cmd, t_env **envs)
{
	(void)envs;
	g_force_exit = 0;
	if (cmd->args && cmd->args[1])
		g_force_exit = ft_atoi(cmd->args[1]);
	printf("exit\n"); // This musn't be printf when it's in a pipe...
	return (g_force_exit);
}
