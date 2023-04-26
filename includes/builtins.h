/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:34:03 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/26 17:48:23 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "types/command.h"
# include "types/env.h"

void	cmd_echo(t_cmd *cmd);
void	cmd_env(t_cmd *cmd);

#endif
