/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:58:58 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/26 22:33:35 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "types/env.h"
#include "libft.h"

static void	put_args(t_env *env, t_cmd_arg *args)
{
	t_env	*var_env;

	while (args)
	{
		if (args->type == CONCATENATION)
			put_args(env, args->data);
		else if (args->type == VARIABLE)
		{
			var_env = get_env(env, args->data);
			if (var_env)
				ft_putstr_fd(var_env->value, STDOUT_FILENO);
		}
		else
			ft_putstr_fd(args->data, STDOUT_FILENO);
		if (args->next)
			ft_putchar_fd(' ', STDOUT_FILENO);
		args = args->next;
	}
}

void	builtin_echo(t_cmd *cmd)
{
	put_args(cmd->env, cmd->args);
	ft_putchar_fd('\n', STDOUT_FILENO);
}
