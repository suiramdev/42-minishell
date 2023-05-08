/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:03:54 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/08 16:27:48 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Get an environment variable from the list
/// @param envs The head of the list of environment variables
/// @param key The key of the environment variable to get
/// @return The environment variable, or NULL if it was not found
t_env	*get_env(t_env *envs, char *key)
{
	t_env	*tmp;

	tmp = envs;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/// @brief Add or replace an environment variable to the list
/// @param envs The head of the list of environment variables, NULL accepted
/// @param key The key of the new environment variable
/// @param value The value of the new environment variable
/// @return The new environment variable
t_env	*add_env(t_env **envs, char *key, char *value)
{
	t_env	*new;
	t_env	*last;

	new = get_env(*envs, key);
	if (new)
	{
		free(new->value);
		new->value = value;
		return (new);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!*envs)
	{
		*envs = new;
		return (new);
	}
	last = *envs;
	while (last->next)
		last = last->next;
	last->next = new;
	return (new);
}

/// @brief Remove an environment variable from the list
/// @param envs The envs of the list of environment variables
/// @param key The key of the environment variable to remove
/// @return The envs of the list, or NULL if the environment
/// variable was not found
t_env	*remove_env(t_env *envs, char *key)
{
	t_env	*tmp;

	tmp = envs;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key)
				+ ft_strlen(key)) == 0)
		{
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (envs);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

/// @brief Free the list of environment variables
/// @param list The envs of the list of environment variables
/// @return void
void	free_envs(t_env *envs)
{
	t_env	*tmp;

	while (envs)
	{
		tmp = envs;
		envs = envs->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

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