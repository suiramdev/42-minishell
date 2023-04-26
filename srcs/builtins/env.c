/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:31 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/26 17:48:51 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "libft.h"

void	builtin_env(t_cmd *cmd)
{
	char	**formatted_env;
	size_t	i;

	formatted_env = format_env(cmd->env);
	i = 0;
	while (formatted_env[i])
		ft_putendl_fd(formatted_env[i++], STDOUT_FILENO);
	i = 0;
	while (formatted_env[i])
		free(formatted_env[i++]);
	free(formatted_env);
}
