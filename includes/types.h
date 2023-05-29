/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:31:23 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/22 15:36:10 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <sys/types.h>
# include <stdbool.h>

// types/env.c
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*get_env(t_env *envs, char *key);
t_env	*set_env(t_env **envs, char *key, char *value);
t_env	*remove_env(t_env **envs, char *key);
void	free_env(t_env *envs);

// types/token.c
char	**tokenize(char *line, t_env *envs);

// types/cmd.c
typedef struct s_cmd
{
	char			*name;
	char			**args;
	int				infile;
	int				outfile;
	bool			has_heredoc;
	bool			has_pipe;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

void	add_cmd(t_cmd **cmds, t_cmd *new);
t_cmd	*new_cmd(char **tokens, size_t start, size_t end);
char	*last_cmd_arg(t_cmd *cmds);
void	free_cmds(t_cmd *cmds);

#endif
