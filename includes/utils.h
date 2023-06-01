/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:46:24 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/01 18:19:20 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"
# include <stddef.h>
# include <stdbool.h>

// utils/exec/redirs.c
# define HEREDOC_FILE ".heredoc"

bool	init_redirs(char **tokens, size_t i, t_cmd *node);
void	redirs(t_cmd *cmd);
void	close_redirs(t_cmd *cmds);
void	redir_heredoc2(t_cmd *cmd);

// utils/exec/pipeline.c
int		pipeline(t_cmd *cmds, t_env **envs);

// utils/exec/process.c
int		wait_processes(t_cmd *cmds);
bool	is_child_process(t_cmd *cmds);

// utils/exec/exec.c
# define BUILTIN_NOT_FOUND -1

int		exec_builtin(t_cmd *cmd, t_env **envs);
int		exec_relative(t_cmd *cmd, t_env **envs);
int		exec_cmds(t_cmd *cmds, t_env **envs);

// utils/parse/errors.c
bool	handle_unexpected(char ***tokens);

// utils/parse/free.c
void	free_tokens(char **tokens);

// utils/parse/str.c
bool	is_space(char c);
void	skip_spaces(char *line, size_t *i);
bool	handle_quotes(char *line, size_t *i);
void	increase_token_index(size_t *count, size_t *i);

// utils/parse/trim.c
char	*replace_env_var(t_env *envs, char *token,
			bool *split_token, char *tokenpre);
char	*trim_token_quote(char **token);

// utils/env.c
char	**format_env(t_env *envs);

// utils/error.c
void	error(char *msg, char *more);
void	error_heredoc(char *delimiter);
void	error_invalid_identifier(char *name, char *arg);
void	error_write(char *cmd);

// utils/path.c
char	*join_path(char *s1, char *s2);
char	*resolve_path(char *file, t_env *envs, int perms);

// utils/pipes.c
bool	has_pipes(char *str);
bool	valid_last_command(char **tokens, size_t i);
void	cmds_has_pipes(t_cmd *cmds);

// utils/signal.c
void	main_signal(int signal);
void	heredoc_signal(int signal);
void	cmd_signal(int signal);

// utils/token.c
char	**token_split(char **tokens, size_t *i, bool *split_token, int k);
int		check_end_by_quote(char *line, int i);
bool	special_char(char c);
int		isinquote(char *token, size_t *i);

#endif
