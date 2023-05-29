/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:57:35 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/27 00:54:46 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Print an error message when an invalid identifier is given
/// @param identifier The name of the command that was executed
/// @param arg The argument that was wrong
void	error_identifier(char *identifier)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

/// @brief Execute the export builtin command
/// @param cmd The command to execute
/// @param envs The environment variables
/// @return The exit status
int	builtin_export(t_cmd *cmd, t_env **envs)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (cmd->args && cmd->args[i])
	{
		j = 0;
		while (cmd->args[i][j] && cmd->args[i][j] != '=')
		{
			if ((cmd->args[i][0] >= '0' && cmd->args[i][0] <= '9')
				|| special_char(cmd->args[i][j]))
				return (error_identifier(cmd->args[i]), EXIT_FAILURE);
			j++;
		}
		if (j == 0)
			return (error_identifier(&cmd->args[i][j]), EXIT_FAILURE);
		if (cmd->args[i][j])
		{
			cmd->args[i][j] = '\0';
			if (!set_env(envs, cmd->args[i], ft_strdup(&cmd->args[i][j + 1])))
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
