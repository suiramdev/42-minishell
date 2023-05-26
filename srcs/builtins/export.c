/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:57:35 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/26 16:27:58 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_cmd *cmd, t_env **envs)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (cmd->args && cmd->args[i])
	{
		j = 0;
		while (cmd->args[i][j] && cmd->args[i][j] != '=')
			j++;
		if (j == 0)
			return (error_invalid_identifier("export", cmd->args[i] + j), EXIT_FAILURE);
		if (cmd->args[i][j] == '=')
		{
			cmd->args[i][j] = '\0';
			if (!set_env(envs, cmd->args[i], ft_strdup(&cmd->args[i][j + 1])))
				return (EXIT_FAILURE);
			cmd->args[i][j] = '=';
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
