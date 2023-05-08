/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:57:35 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/08 16:25:36 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Issue there, is that cmd->env is a copy of the env,
// not the actual env we should make it a pointer to env,
// and have also its own copy of the env maybe
int	builtin_export(t_cmd *cmd, t_env *envs)
{
	(void)cmd;
	(void)envs;
	return (EXIT_SUCCESS);
}