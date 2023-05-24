/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:51:22 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/24 16:51:49 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Waits for all the processes to finish
/// @param cmds The commands to execute
void	wait_processes(t_cmd *cmds, t_env **envs)
{
	int		status;

	status = 0;
	while (cmds)
	{
		waitpid(cmds->pid, &status, 0);
		set_env(envs, "?", ft_itoa(WEXITSTATUS(status)));
		cmds = cmds->next;
	}
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
