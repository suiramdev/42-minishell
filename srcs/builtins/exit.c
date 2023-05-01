/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:39 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/01 16:41:49 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "libft.h"

/// @brief Execute the exit builtin command
/// @param cmd The command to execute
void	builtin_exit(t_cmd *cmd)
{
	int		exit_code;

	exit_code = 0;
	if (cmd->args && cmd->args[1])
		exit_code = ft_atoi(cmd->args[1]);
	exit(exit_code);
}
