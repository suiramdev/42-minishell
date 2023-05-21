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
/// @note The key and value are duplicated
t_env	*set_env(t_env **envs, char *key, char *value)
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
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (*envs)
	{
		last = *envs;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*envs = new;
	return (new);
}

/// @brief Remove an environment variable from the list
/// @param envs The head of the list of environment variables
/// @param key The key of the environment variable to remove
/// @return The new head of the list of environment variables
/// or NULL if the environment variable was not found
t_env	*remove_env(t_env **envs, char *key)
{
	t_env	*current;
	t_env	*tmp;

	if (!*envs)
		return (NULL);
	if (ft_strcmp((*envs)->key, key) == 0)
	{
		tmp = *envs;
		*envs = (*envs)->next;
		free_env(tmp);
		return (*envs);
	}
	current = *envs;
	while (current->next)
	{
		if (ft_strcmp(current->next->key, key) == 0)
		{
			tmp = current->next;
			current->next = current->next->next;
			free_env(tmp);
			return (*envs);
		}
		current = current->next;
	}
	return (NULL);
}

/// @brief Free an environment variable
/// @param envs The environment variable to free
void	free_env(t_env *envs)
{
	free(envs->key);
	free(envs->value);
	free(envs);
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
