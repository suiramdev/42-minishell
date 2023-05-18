/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:34:40 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/17 16:18:59 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types/command.h"
# include <stddef.h>
# include <stdbool.h>

bool	is_space(char c);
void	skip_spaces(char *line, size_t *inc);
bool	handle_quotes(char *line, size_t *inc);
bool	has_pipes(char *str);
bool	valid_last_command(char **tokens, size_t i);
void	cmds_has_pipes(t_cmd *cmds);
void	increase_token_index(size_t *count, size_t *i);

#endif
