#include "minishell.h"

/// @brief Print an error message to the standard error
/// @param msg The main error message
/// @param more Additional error information
void	ft_errorendl(char *msg, char *more)
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

/// @brief Print an error message to the standard error related to a heredoc operation.
/// @param delimiter The delimiter that was expected and not found, leading to the end of file.
void heredoc_error(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by end-of-file ", STDERR_FILENO);
	ft_putstr_fd("(wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}