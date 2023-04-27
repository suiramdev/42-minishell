/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:39 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/27 00:23:08 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "libft.h"

void	builtin_exit(t_cmd *cmd)
{
	int		exit_code;

	exit_code = 0;
	if (cmd->args && cmd->args[1])
		exit_code = ft_atoi(cmd->args[1]);
	exit(exit_code);
}
