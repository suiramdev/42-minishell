/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:46:24 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/26 02:00:50 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"
# include <stddef.h>
# include <stdbool.h>

// utils/error.c
void	error(char *msg, char *more);
void	error_heredoc(char *delimiter);
void	error_numerical_arg(char *name, char *arg);

// utils/signal.c
void	main_signal(int signal);
void	cmd_signal(int signal);

// utils/str.c
bool	is_space(char c);
void	skip_spaces(char *line, size_t *i);
bool	handle_quotes(char *line, size_t *i);
void	increase_token_index(size_t *count, size_t *i);

// utils/pipes.c
bool	has_pipes(char *str);
bool	valid_last_command(char **tokens, size_t i);
void	cmds_has_pipes(t_cmd *cmds);

// utils/token.c
char	*trim_token_quote(char **token);
void	free_tokens(char **tokens);
char	*replace_env_var(t_env *envs, char *token);

// utils/token2.c
int		unexpected_token(char **tokens);
void	unexpected_token_error(char *token);
void	isquotefill(char *quote, char c);
bool	special_char(char c);

// utils/env.c
char	**format_env(t_env *envs);

// utils/path.c
char	*join_path(char *s1, char *s2);
char	*resolve_path(char *file, t_env *envs);

// utils/exec/redirs.c
# define HEREDOC_FILE ".heredoc"

bool	init_redirs(char **tokens, size_t i, t_cmd *node);
void	redirs(t_cmd *cmd);
void	close_redirs(t_cmd *cmds);

// utils/exec/pipeline.c
int		pipeline(t_cmd *cmds, t_env **envs);

// utils/exec/process.c
void	wait_processes(t_cmd *cmds, t_env **envs);
bool	is_child_process(t_cmd *cmds);

// utils/exec/exec.c
# define BUILTIN_NOT_FOUND -1

int		exec_builtin(t_cmd *cmd, t_env **envs);
int		exec_relative(t_cmd *cmd, t_env **envs);
int		exec_cmds(t_cmd *cmds, t_env **envs);

#endif
