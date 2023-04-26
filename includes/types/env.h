/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:02:27 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/27 00:25:01 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*get_env(t_env *head, char *key);
t_env	*add_env(t_env **head, char *key, char *value);
t_env	*remove_env(t_env *head, char *key);
void	free_envs(t_env *head);
char	**format_env(t_env *head);

#endif
