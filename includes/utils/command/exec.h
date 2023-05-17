/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:33:06 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/17 10:07:04 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "types/command.h"
# include "types/env.h"

# define BUILTIN_NOT_FOUND -1

int	exec_builtin(t_cmd *cmd, t_env **envs);
int	exec_relative(t_cmd *cmd, t_env **envs);

#endif
