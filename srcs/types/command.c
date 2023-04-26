/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:28:40 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/27 01:47:21 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "builtins.h"
#include <stdlib.h>
#include <stdio.h>

/// @brief Create new commands for testing purposes
/// @param env The environment variables linked list
/// @return The list of commands, or NULL if an error occurred
/// @note This function is temporary, it will be replaced by the parser.
/// It may contain memory leaks, it is not intended to be used in production
t_cmd	*example_cmds(t_env *env)
{
	t_cmd		*cmd;
	t_cmd_arg	*arg1;
	t_cmd_arg	*arg2;
	t_cmd_arg	*arg2_1;
	t_cmd_arg	*arg2_2;

	cmd = malloc(sizeof(t_cmd));
	cmd->env = env;
	cmd->name = "echo";
	arg2_2 = malloc(sizeof(t_cmd_arg));
	arg2_2->type = VARIABLE;
	arg2_2->data = "USER";
	arg2_2->next = NULL;
	arg2_1 = malloc(sizeof(t_cmd_arg));
	arg2_1->type = LITERAL;
	arg2_1->data = "\nHow are you";
	arg2_1->next = arg2_2;
	arg2 = malloc(sizeof(t_cmd_arg));
	arg2->type = CONCATENATION;
	arg2->data = arg2_1;
	arg2->next = NULL;
	arg1 = malloc(sizeof(t_cmd_arg));
	arg1->type = LITERAL;
	arg1->data = "Hello !";
	arg1->next = arg2;
	cmd->args = arg1;
	return (cmd);
}

/// @brief Execute a list of commands
/// @param cmds The list of commands to execute
/// @return EXIT_SUCCESS if the command was executed successfully, EXIT_FAILURE otherwise
int	exec_cmds(t_cmd *cmds)
{
	while (cmds)
	{
		if (builtins(cmds) == EXIT_FAILURE)
		{
			printf("Command not found: %s\n", cmds->name);
			// execve in a fork, and maybe builtins should be in a fork too
		}
		cmds = cmds->next;
	}
	return (EXIT_SUCCESS);
}
