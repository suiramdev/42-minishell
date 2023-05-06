#include "../../includes/minishell.h"

t_data	*ft_listlast(t_data *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_listadd_back(t_data **lst, t_data *new)
{
	t_data	*last;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		last = ft_listlast(*lst);
		last->next = new;
	}
}

int valid_last_command(char **tokens, int i)
{
    if (tokens[i][0] == '|' && tokens[i + 1][0] == '>' && !tokens[i + 3])
        return (0);
    return (1);
}