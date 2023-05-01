/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:44:04 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/01 18:20:27 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "types/env.h"
# include <sys/types.h>

typedef struct s_cmd
{
	char			*name;
	char			**args;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*last_cmd(t_cmd *cmds);
void	add_cmd(t_cmd **cmds, t_cmd *new);
t_cmd	*new_cmd(char **tokens, int start, int end);
t_cmd	*init_cmds(char **tokens);
int		exec_cmds(t_cmd *cmds, t_env *envs);

#endif
