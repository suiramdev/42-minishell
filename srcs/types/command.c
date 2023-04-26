/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:28:40 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/26 17:24:39 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "builtins.h"
#include <stdlib.h>

/// @brief Create a new prompt
/// @return The new prompt, or NULL if an error occured
/// @note This function is temporary, it will be replaced by the parser.
/// It may contain memory leaks, it is not intended to be used in production
t_cmd	*example_cmd(t_env *env)
{
	t_cmd		*cmd;
	t_cmd_arg	*arg1;
	t_cmd_arg	*arg2;

	cmd = malloc(sizeof(t_cmd));
	cmd->env = env;
	cmd->name = "echo";
	arg2 = malloc(sizeof(t_cmd_arg));
	arg2->type = VARIABLE;
	arg2->value = "USER";
	arg2->next = NULL;
	arg1 = malloc(sizeof(t_cmd_arg));
	arg1->type = STRING;
	arg1->value = "Hello";
	arg1->next = arg2;
	cmd->args = arg1;
	return (cmd);
}

/// @brief Execute a prompt
/// @param prompt The prompt to execute
/// @return The exit status of the prompt
int	exec_cmd(t_cmd *cmd)
{
	cmd_echo(cmd);
	return (EXIT_SUCCESS);
}
