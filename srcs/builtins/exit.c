/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:39 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/05 14:55:29 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "libft.h"

/// @brief Execute the exit builtin command
/// @param cmd The command to execute
/// @param envs The environment variables
int	builtin_exit(t_cmd *cmd, t_env *envs)
{
	int		exit_code;

	(void)envs;
	exit_code = 0;
	if (cmd->args && cmd->args[1])
		exit_code = ft_atoi(cmd->args[1]);
	return (exit_code);
}
