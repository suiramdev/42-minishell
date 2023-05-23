/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 01:07:56 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/22 01:21:41 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Format the list of environment variables to an array of strings
/// ending with NULL
/// @param envs The envs of the list of environment variables
/// @return The array of strings, or NULL if an error occured
char	**format_env(t_env *envs)
{
	size_t	i;
	t_env	*tmp;
	char	**output;

	i = 0;
	tmp = envs;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	output = malloc(sizeof(char *) * (i + 1));
	if (!output)
		return (NULL);
	i = 0;
	tmp = envs;
	while (tmp)
	{
		output[i] = ft_strjoin(tmp->key, "=");
		output[i] = ft_strjoin(output[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	output[i] = NULL;
	return (output);
}
