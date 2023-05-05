/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:30:39 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/05 14:30:41 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "builtins.h"
#include "utils/path.h"
#include "utils/parsing.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/// @brief Create a new command from the tokens array
/// @param tokens The tokens array
/// @param start The start index of the command in the tokens array
/// @param end The end index of the command in the tokens array
/// @return The new command
t_cmd	*new_cmd(char **tokens, int start, int end)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = ft_strdup(tokens[start]);
	cmd->args = (char **)malloc((end - start + 1) * sizeof(char *));
	if (!cmd->args)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		cmd->args[i] = ft_strdup(tokens[start + i]);
		i++;
	}
	cmd->args[i] = NULL;
	cmd->next = NULL;
	return (cmd);
}

/// @brief Add a command to the commands linked list
/// @param cmds The commands linked list
/// @param new The command to add
void	add_cmd(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*last;

	if (new)
	{
		if (!*cmds)
		{
			*cmds = new;
			return ;
		}
		last = *cmds;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

/// @brief Free the commands linked list
/// @param cmds The commands linked list
void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	size_t	i;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free(tmp->name);
		i = 0;
		while (tmp->args[i])
			free(tmp->args[i++]);
		free(tmp->args);
		free(tmp);
	}
}
