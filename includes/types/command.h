/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:44:04 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/26 20:08:55 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "types/env.h"

enum e_arg_types
{
	LITERAL,
	VARIABLE,
	CONCATENATION,
};

typedef struct s_cmd_arg
{
	enum e_arg_types	type;
	void				*data;
	struct s_cmd_arg	*next;
}	t_cmd_arg;

typedef struct s_cmd
{
	char			*name;
	t_cmd_arg		*args;
	t_env			*env;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*example_cmds(t_env *env);
int		exec_cmds(t_cmd *cmds);

#endif
