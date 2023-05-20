/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:28:51 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/19 16:36:53 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "types/command.h"
# include <stddef.h>

bool	has_pipes(char *str);
bool	valid_last_command(char **tokens, size_t i);
void	cmds_has_pipes(t_cmd *cmds);

#endif
