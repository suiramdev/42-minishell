/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:56 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/08 16:25:54 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// See issue in export.c
int	builtin_unset(t_cmd *cmd, t_env **envs)
{
	if (!cmd->args[1])
		return (EXIT_FAILURE);
	if (!remove_env(envs, cmd->args[1]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
