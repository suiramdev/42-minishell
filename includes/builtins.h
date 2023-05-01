/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:34:03 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/01 18:23:18 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "types/command.h"
# include "types/env.h"

typedef struct s_builtin
{
	char	*name;
	void	(*func)(t_cmd *cmd, t_env *envs);
}	t_builtin;

void	builtin_cd(t_cmd *cmd, t_env *envs);
void	builtin_echo(t_cmd *cmd, t_env *envs);
void	builtin_env(t_cmd *cmd, t_env *envs);
void	builtin_exit(t_cmd *cmd, t_env *envs);
void	builtin_export(t_cmd *cmd, t_env *envs);
void	builtin_pwd(t_cmd *cmd, t_env *envs);
void	builtin_unset(t_cmd *cmd, t_env *envs);

int		builtins(t_cmd *cmd, t_env *envs);

#endif
