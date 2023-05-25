/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:56 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/26 01:54:48 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// See issue in export.c
int	builtin_unset(t_cmd *cmd, t_env **envs)
{
	size_t	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!remove_env(envs, cmd->args[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
