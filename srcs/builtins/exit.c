/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:39 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/27 02:36:48 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check if the arguments are numerical
/// @param args The arguments to check
/// @param non_numerical_arg The variable to store the first
/// non numerical argument
/// @return true if the arguments are numerical, false otherwise
static bool	numerical_args(char **args, char **non_numerical_arg)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		if (args[i][0] == '-' || args[i][0] == '+')
			j++;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
			{
				*non_numerical_arg = args[i];
				return (false);
			}
			j++;
		}
		i++;
	}
	*non_numerical_arg = NULL;
	return (true);
}

/// @brief Print an error message to the standard error related
/// a wrong numerical argument.
/// @param name The name of the command that was executed
/// @param arg The argument that was wrong
static void	error_numerical_arg(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

/// @brief Execute the exit builtin command
/// @param cmd The command to execute
/// @param envs The environment variables
/// @return The exit status
/// @note Should be executed in the main process
int	builtin_exit(t_cmd *cmd, t_env **envs)
{
	char	*non_numerical_arg;

	(void)envs;
	if (!numerical_args(cmd->args + 1, &non_numerical_arg))
	{
		g_force_exit = 2;
		return (error_numerical_arg(non_numerical_arg), 2);
	}
	if (cmd->args[1])
	{
		if (cmd->args[2])
			return (error("exit", "too many arguments"), EXIT_FAILURE);
		g_force_exit = ft_atoi(cmd->args[1]);
	}
	else
		g_force_exit = 0;
	if (!cmd->has_pipe)
		printf("exit\n");
	return (g_force_exit);
}
