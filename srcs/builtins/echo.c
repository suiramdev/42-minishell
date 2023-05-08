/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:58:58 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/08 16:24:58 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Execute the echo builtin command
/// @param cmd The command data structure
/// @param envs The environment variables
/// @return EXIT_SUCCESS
/// @todo Handle the -n option
/// we should have a custom printf function in order to skip quotes and replace environment variables
int	builtin_echo(t_cmd *cmd, t_env *envs)
{
	size_t	i;

	(void)envs;
	i = 1;
	while (cmd->args && cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
	return (EXIT_SUCCESS);
}
