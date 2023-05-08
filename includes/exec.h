/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:53:58 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/08 17:12:17 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "types/command.h"
# include "types/env.h"

# define BUILTIN_NOT_FOUND -1

int	exec(t_cmd *cmds, t_env *envs);

#endif