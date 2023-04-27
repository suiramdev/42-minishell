/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:48 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/27 00:22:33 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "libft.h"
#include <stdio.h>

/// @brief Execute the pwd builtin command
/// @param cmd The command data structure
void	builtin_pwd(t_cmd *cmd)
{
	char	path[1024];

	if (cmd->args)
	{
		ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
		return ;
	}
	if (!getcwd(path, 1024))
		perror("pwd");
	else
		printf("%s\n", path);
}
