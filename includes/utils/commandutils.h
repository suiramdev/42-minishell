#ifndef COMMANDUTILS_H

# define COMMANDUTILS_H

int	has_pipes(char *str);
int valid_last_command(char **tokens, int i);
void	cmds_has_pipes(t_cmd *cmds);

#endif
