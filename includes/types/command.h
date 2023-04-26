/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:44:04 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/26 16:34:53 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "types/env.h"

enum e_arg_types
{
	STRING,
	VARIABLE,
};

typedef struct s_cmd_arg
{
	enum e_arg_types	type;
	char				*value;
	struct s_cmd_arg	*next;	
}	t_cmd_arg;

typedef struct s_cmd_redir
{
	int					*fd;
	char				*operator;
	char				*file;
	struct s_cmd_redir	*next;	
}	t_cmd_redir;

typedef struct s_cmd
{
	char			*name;
	t_cmd_arg		*args;
	t_cmd_redir		*redirects;
	struct s_cmd	*next;
	t_env			*env;
}	t_cmd;

t_cmd	*example_cmd(t_env *env);
int		exec_cmd(t_cmd *cmd);

#endif
