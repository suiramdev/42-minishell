/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:58:58 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/26 16:52:08 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "types/env.h"
#include "libft.h"

void	cmd_echo(t_cmd *cmd)
{
	t_env	*env;

	while (cmd->args)
	{
		if (cmd->args->type == VARIABLE)
		{
			env = get_env(cmd->env, cmd->args->value);
			if (env)
				ft_putstr_fd(env->value, STDOUT_FILENO);
		}
		else
			ft_putstr_fd(cmd->args->value, STDOUT_FILENO);
		if (cmd->args->next)
			ft_putchar_fd(' ', STDOUT_FILENO);
		cmd->args = cmd->args->next;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}
