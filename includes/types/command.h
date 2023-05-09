/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:44:04 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/08 18:54:14 by mnouchet         ###   ########.fr       */
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
	int				infile;
	int				outfile;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

void	add_cmd(t_cmd **cmds, t_cmd *new);
t_cmd	*new_cmd(char **tokens, size_t start, size_t end);
t_cmd	*init_cmds(char **tokens);
void	free_cmds(t_cmd *cmds);

#endif
