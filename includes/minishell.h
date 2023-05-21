/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:37:48 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/19 17:30:07 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "types/command.h"
# include "types/env.h"
# include "types/token.h"
# include "utils/command/args.h"
# include "utils/command/exec.h"
# include "utils/command/pipeline.h"
# include "utils/command/pipes.h"
# include "utils/command/redirs.h"
# include "utils/error.h"
# include "utils/parsing.h"
# include "utils/path.h"
# include "utils/signal.h"
# include "utils/command/exec.h"
# include "utils/command/pipes.h"
# include "utils/command/redirs.h"
# include "builtins.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <string.h>

extern int	g_force_exit;

#endif
