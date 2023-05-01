/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:58:49 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/27 00:23:19 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/// @brief Execute the cd builtin command
/// @param cmd The command data structure
void	builtin_cd(t_cmd *cmd)
{
	t_env	*env;
	char	*path;
	
	if (cmd->args && cmd->args[1])
		path = cmd->args[1];
	else
	{
		env = get_env(cmd->env, "HOME");
		if (!env)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return ;
		}
		path = env->value;
	}
	if (chdir(path) == -1)
		perror("cd");
}
