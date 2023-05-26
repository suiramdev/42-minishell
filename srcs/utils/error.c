/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:27:26 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/26 14:58:19 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Print an error message to the standard error with
/// the program name as prefix.
/// @param msg The main error message
/// @param more Additional error information
void	error(char *msg, char *more)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (more)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(more, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}

/// @brief Print an error message to the standard error related
/// to a heredoc operation.
/// @param delimiter The delimiter that was expected and not found,
/// leading to the end of file.
void	error_heredoc(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

/// @brief Print an error message to the standard error related
/// a wrong numerical argument.
/// @param name The name of the command that was executed
/// @param arg The argument that was wrong
void	error_numerical_arg(char *name, char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

/// @brief Print an error message to the standard error related
/// a wrong identifier.
/// @param name The name of the command that was executed
/// @param arg The argument that was wrong
void	error_valid_identifier(char *name, char *arg)
{
	ft_putstr_fd("minishell: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}
