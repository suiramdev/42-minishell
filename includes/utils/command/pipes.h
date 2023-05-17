/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:33:16 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/17 11:28:51 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "types/command.h"
# include "types/env.h"

void	wait_processes(t_cmd *cmds);
int		pipeline(t_cmd *cmds, t_env **envs);

#endif
