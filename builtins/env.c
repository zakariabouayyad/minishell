#include "../minishell.h"

void	print_envp(t_envp **env_lst, int list_size)
{
	t_envp		*tmp;
	int			loc;
	int			size;

	if (!env_lst)
		return ;
	loc = 1;
	size = ft_lstsize_envp(*env_lst);
	while (loc <= list_size)
	{
		tmp = *env_lst;
		while (tmp && loc != tmp->env_order)
			tmp = tmp->next;
		if (tmp && tmp->includes_in_expt != 1)
		{
			if (tmp->shlvl_var != 0)
				printf("%s=%d\n", tmp->variable, tmp->shlvl_var);
			else if (tmp->value == NULL || tmp->value[0] == '\0')
				printf("%s=\n", tmp->variable);
			else
				printf("%s=%s\n", tmp->variable, tmp->value);
		}
		loc++;
	}
	tmp = *env_lst;
	while (tmp && loc-- > 1)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->includes_in_expt != 1)
		{
			if (tmp->shlvl_var != 0)
				printf("%s=%d\n", tmp->variable, tmp->shlvl_var);
			else if (tmp->value == NULL)
				printf("%s=\n", tmp->variable);
			else
				printf("%s=%s\n", tmp->variable, tmp->value);
		}
		tmp = tmp->next;
	}
}