/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:34:40 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/19 16:06:55 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types/command.h"
# include <stddef.h>
# include <stdbool.h>

bool	is_space(char c);
void	skip_spaces(char *line, size_t *i);
bool	handle_quotes(char *line, size_t *i);
void	increase_token_index(size_t *count, size_t *i);

#endif
