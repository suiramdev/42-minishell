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
#include <stdio.h>

/// @brief Execute the echo builtin command
/// @param cmd The command data structure
/// @return EXIT_SUCCESS
/// @todo Handle the -n option
void	builtin_echo(t_cmd *cmd)
{
	size_t	i;

	i = 1;
	while (cmd->args && cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}
