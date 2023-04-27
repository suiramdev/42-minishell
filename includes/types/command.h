/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:44:04 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/27 15:18:58 by mnouchet         ###   ########.fr       */
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
	t_env			*env;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*example_cmds(t_env *env);
int		exec_cmds(t_cmd *cmds);

#endif
