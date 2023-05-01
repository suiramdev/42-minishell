/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:56 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/01 18:22:15 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"

// See issue in export.c
void	builtin_unset(t_cmd *cmd, t_env *envs)
{
	(void)cmd;
	(void)envs;
}
