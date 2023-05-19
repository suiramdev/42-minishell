#include "minishell.h"

/// @brief Check if the line contains pipes
/// @param str The line to check
/// @return 1 if the line contains pipes, 0 otherwise
int	has_pipes(char *str)
{
    int	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '"')
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

/// @brief Validate the last command in the array of tokens
/// @param tokens The array of tokens (parsed command line)
/// @param i The index of the command in the array to validate
/// @return 1 if the command is valid, 0 otherwise
int valid_last_command(char **tokens, int i)
{
    if (tokens[i][0] == '|' && tokens[i + 1][0] == '>' && !tokens[i + 3])
        return (0);
    return (1);
}

/// @brief Set the has_pipe attribute to 1 for each command in the linked list
/// @param cmds A pointer to the first command in the linked list
void	cmds_has_pipes(t_cmd *cmds)
{
	t_cmd *head;

	head = cmds;
	while (head)
	{
		head->has_pipe = 1;
		head = head->next;
	}
}