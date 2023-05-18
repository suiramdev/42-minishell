/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:37:48 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/17 16:07:37 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "types/command.h"
# include "types/env.h"
# include "types/token.h"
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
# include <stdbool.h>

extern int	g_force_exit;

#endif
