/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:03:54 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/27 00:24:46 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/env.h"
#include "libft.h"
#include <stdlib.h>

/// @brief Get an environment variable from the list
/// @param head The head of the list
/// @param key The key of the environment variable to get
/// @return The environment variable, or NULL if it was not found
t_env	*get_env(t_env *head, char *key)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/// @brief Add or replace an environment variable to the list
/// @param head The head of the list, NULL accepted
/// @param key The key of the new environment variable
/// @param value The value of the new environment variable
/// @return The new environment variable
t_env	*add_env(t_env **head, char *key, char *value)
{
	t_env	*new;
	t_env	*last;
	
	new = get_env(*head, key);
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
	if (!*head)
	{
		*head = new;
		return (new);
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
	return (new);
}

/// @brief Remove an environment variable from the list
/// @param head The head of the list
/// @param key The key of the environment variable to remove
/// @return The head of the list, or NULL if the environment variable was not found
t_env	*remove_env(t_env *head, char *key)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key) + ft_strlen(key)) == 0)
		{
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (head);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

/// @brief Free the list of environment variables
/// @param head The head of the list
/// @return void
void	free_envs(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

/// @brief Format the list of environment variables to an array of strings
/// ending with NULL
/// @param head The head of the list
/// @return The array of strings, or NULL if an error occured
char	**format_env(t_env *head)
{
	size_t	i;
	t_env	*tmp;
	char	**env;

	i = 0;
	tmp = head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	tmp = head;
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->key, "=");
		env[i] = ft_strjoin(env[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
