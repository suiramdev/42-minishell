/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:37:48 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/08 17:12:33 by mnouchet         ###   ########.fr       */
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
# include "builtins.h"
# include "exec.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

extern int	g_force_exit;

#endif
