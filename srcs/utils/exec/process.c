/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:51:22 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/01 18:14:02 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Waits for all the processes to finish
/// @param cmds The commands to execute
/// @return The exit code of the last process to finish, or failed
int	wait_processes(t_cmd *cmds)
{
	int		status;

	status = 0;
	while (cmds)
	{
		if (waitpid(cmds->pid, &status, 0) == -1)
			return (perror("waitpid"), WEXITSTATUS(status));
		cmds = cmds->next;
	}
	return (WEXITSTATUS(status));
}

bool	is_child_process(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->pid == 0)
			return (true);
		cmds = cmds->next;
	}
	return (false);
}
