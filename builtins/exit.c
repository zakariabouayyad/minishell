#include "../minishell.h"

void	execute_exit(char *num)
{
	int	status;

	status = ft_atoi(num);
	if (status == 256)
		(printf("exit\n"), exit(0));
	else if (status > 256)
	{
		while (status > 256)
			status -= 256;
		(printf("exit\n"), exit(status));
	}
	else
		(printf("exit\n"), exit(status));
}

void	ft_exit_alpha_error(t_list *tokens)
{
	t_list	*tmp;
	int		i;
	int		j;

	i = 1;
	tmp = tokens->next;
	while (tokens != NULL)
	{
		j = 0;
		while (tokens->content[j] != '\0' && ft_isdigit(tokens->content[j]) == 1)
			j++;
		if (tokens->content[j] == '\0' && ++i)
			tokens = tokens->next;
		else if (++i)
		{
			tokens = tokens->next;
			break ;
		}
	}
	if (i == 1)
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n", tokens->content);
		exit(NAR);
	}
	else if ((tokens->content != NULL || ft_isdigit(tokens->prev->content[j]) == 0) && i != 2)
		printf("exit\nminishell: exit: too many arguments\n");
	else
		execute_exit(tmp->content);
}

void	ft_exit(t_list *tokens)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	if (i == 1)
	{
		printf("exit\n");
		exit(0);
	}
	else if (i >= 2)
		ft_exit_alpha_error(tokens);
}