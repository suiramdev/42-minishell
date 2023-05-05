/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:48 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/05 14:56:23 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

/// @brief Execute the pwd builtin command
/// @param cmd The command data structure
int	builtin_pwd(t_cmd *cmd)
{
	char	path[1024];

	if (cmd->args && cmd->args[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!getcwd(path, 1024))
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", path);
	return (EXIT_SUCCESS);
}
