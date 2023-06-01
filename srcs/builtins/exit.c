/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:39 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/01 17:22:56 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

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

/// @brief Check if the arguments are numerical @param args The arguments to check
/// @param non_numerical_arg The variable to store the first
/// non numerical argument
/// @return true if the arguments are numerical, false otherwise
static int	verify_args(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][0] == '-' || args[i][0] == '+')
			j++;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
				return (error_numerical_arg(args[i]), 2);
			j++;
		}
		if (args[i + 1])
		{
			g_minishell.force_exit = false;
			return (error("exit", "too many arguments"), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static bool is_overflowing(const char *s)
{
    bool is_negative;

    is_negative = false;
    if (s && *s == '-')
		is_negative = true;
	if (ft_strlen(s) - is_negative > 19)
		return true;
	if (is_negative && ft_strcmp(s + 1, "9223372036854775808") > 0)
		return true;
    else if (!is_negative && ft_strcmp(s, "9223372036854775807") > 0)
		return true;
    return false;
}

static void	exit_error(char *num)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(num, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

/// @brief Execute the exit builtin command
/// @param cmd The command to execute
/// @param envs The environment variables
/// @return The exit status
/// @note Should be executed in the main process
int	builtin_exit(t_cmd *cmd, t_env **envs)
{
	int		verify_status;

	(void)envs;
	g_minishell.force_exit = true;
	verify_status = verify_args(cmd->args);
	if (verify_status != EXIT_SUCCESS)
		return (verify_status);
	if (!cmd->has_pipe)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (is_overflowing(cmd->args[1]))
		return (exit_error(cmd->args[1]), 0);
	if (cmd->args[1])
		return (ft_atoi(cmd->args[1]));
	return (EXIT_SUCCESS);
}