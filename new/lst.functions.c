#include "minishell.h"

t_envp	*ft_lstlast(t_envp *lst)
{
	t_envp	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

t_envp	*ft_lstnew(char *_variable, char *_value, int _shlvl_var)
{
	t_envp	*node;

	node = NULL;
	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	node->variable = _variable;
	node->value = _value;
	node->shlvl_var = _shlvl_var;
	node->includes_in_expt = 0;
	node->env_order = 0;
	node->end_exp = 0;
	node->chose = -1;
	node->next = 0;
	return (node);
}

void	ft_lstadd_back(t_envp **lst, t_envp *new)
{
	t_envp	*last;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
	}
}

int	ft_lstsize(t_envp *lst)
{
	int	i;

	i = 0;
	while (lst && i++ >= 0)
		lst = lst->next;
	return (i);
}
