/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 23:16:48 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/01 18:18:31 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/env.h"
#include "libft.h"
#include <unistd.h>

/// @brief Join two path together with a '/' between them
/// @param s1 First path
/// @param s2 Second path
/// @return The joined path, or NULL if an error occured
char	*join_path(char *s1, char *s2)
{
	char	*output;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	if (s1[s1_len - 1] == '/')
		s1_len--;
	s2_len = ft_strlen(s2);
	if (s2[0] == '/')
		s2_len--;
	output = malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!output)
		return (NULL);
	ft_memcpy(output, s1, s1_len);
	output[s1_len] = '/';
	ft_memcpy(output + s1_len + 1, s2, s2_len);
	output[s1_len + s2_len + 1] = '\0';
	return (output);
}

/// @brief Resolve a path from a file name based on the PATH environment 
/// variable or the current directory if the file name is a relative path
/// @param file The file name to resolve
/// @param envs The environment variables
/// @return The resolved path, or NULL if an error occured
char	*resolve_path(char *file, t_env *envs)
{
	t_env	*path;
	char	**paths;
	size_t	i;
	char	*output;

	if (!file)
		return (NULL);
	if (access(file, F_OK) >= 0)
		return (ft_strdup(file));
	path = get_env(envs, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path->value, ':');
	i = 0;
	while (paths[i])
	{
		output = join_path(paths[i], file);
		if (access(output, F_OK) >= 0)
			break ;
		free(output);
		output = NULL;
		free(paths[i++]);
	}
	free(paths);
	return (output);
}
