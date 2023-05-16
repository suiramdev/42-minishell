/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:34:40 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/01 16:44:04 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stddef.h>

int		is_space(char c);
void	skip_spaces(char *line, size_t *i);
int		skip_quotes(char *line);
int		handle_quotes(char *line, size_t *i);
void    increase_token_index(size_t *count, size_t *i);
int		has_pipes(char *str);
int		valid_last_command(char **tokens, int i);
void	cmds_has_pipes(t_cmd *cmds);

#endif
