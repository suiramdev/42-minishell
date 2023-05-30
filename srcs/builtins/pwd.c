/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:48 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/30 15:35:40 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Execute the pwd builtin command
/// @param cmd The command data structure
/// @param envs The environment variables
/// @return EXIT_SUCCESS or EXIT_FAILURE if an error occured
int	builtin_pwd(t_cmd *cmd, t_env **envs)
{
	char	path[1024];

	(void)envs;
	(void)cmd;
	if (!getcwd(path, 1024))
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	if (printf("%s\n", path) < 0)
		return (error_write("pwd"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
