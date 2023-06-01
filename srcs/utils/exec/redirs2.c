/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:11:35 by zdevove           #+#    #+#             */
/*   Updated: 2023/06/01 18:13:47 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_heredoc2(t_cmd *cmd)
{
	rl_getc_function = rl_getc;
	close(cmd->infile);
	unlink(HEREDOC_FILE);
}
