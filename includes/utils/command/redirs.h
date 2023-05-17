/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:33:26 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/17 09:58:44 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRS_H
# define REDIRS_H

# include "types/command.h"

# define HEREDOC_FILE "/tmp/heredoc"

int		init_redirs(char **tokens, int i, t_cmd *node);
void	redirs(t_cmd *cmd);
void	close_redirs(t_cmd *cmds);

#endif
