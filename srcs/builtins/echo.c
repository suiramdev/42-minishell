/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:58:58 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/30 15:35:15 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handle the options of the echo builtin command
/// @param args The arguments of the command
/// @param n_option The n option variable to set
/// @return The amount of arguments to skip
static int	handle_options(char **args, bool *n_option)
{
	size_t	i;
	size_t	j;

	*n_option = false;
	i = 1;
	while (args && args[i])
	{
		if (args[i][0] != '-')
			break ;
		j = 1;
		while (args[i][j])
		{
			if (args[i][j] != 'n')
			{
				if (i == 1)
					*n_option = false;
				return (i - 1);
			}
			*n_option = true;
			j++;
		}
		i++;
	}
	return (i - 1);
}

/// @brief Execute the echo builtin command
/// @param cmd The command data structure
/// @param envs The environment variables
/// @return EXIT_SUCCESS or EXIT_FAILURE if an error occured
/// @todo Handle the -n option
/// we should have a custom printf function in order to skip quotes
/// and replace environment variables
int	builtin_echo(t_cmd *cmd, t_env **envs)
{
	bool	n_option;
	size_t	i;

	(void)envs;
	i = 1 + handle_options(cmd->args, &n_option);
	while (cmd->args && cmd->args[i])
	{
		if (cmd->args[i][0])
		{
			if (printf("%s", cmd->args[i]) < 0)
				return (error_write("echo"), EXIT_FAILURE);
			if (cmd->args[i + 1])
				if (printf(" ") < 0)
					return (error_write("echo"), EXIT_FAILURE);
		}
		i++;
	}
	if (!n_option)
		if (printf("\n") < 0)
			return (error_write("echo"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
