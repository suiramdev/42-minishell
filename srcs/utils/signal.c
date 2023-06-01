/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:36:16 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/30 15:37:24 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handle the signals for the main process
/// @param signal The signal to handle
void	main_signal(int signal)
{
	g_minishell.signal = signal;
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		set_env(&g_minishell.envs, "?",
			ft_strdup(ft_itoa(128 + g_minishell.signal)));
	}
}

/// @brief Handle the signals for the herdoc 
/// @param signal The signal to handle
void	heredoc_signal(int signal)
{
	g_minishell.signal = signal;
	set_env(&g_minishell.envs, "?",
		ft_strdup(ft_itoa(128 + g_minishell.signal)));
}

/// @brief Handle the signals for the command execution
/// @param signal The signal to handle
void	cmd_signal(int signal)
{
	g_minishell.signal = signal;
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (signal == SIGQUIT)
	{
		ft_putendl_fd("Quit", STDERR_FILENO);
	}
}
