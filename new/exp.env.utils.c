#include "minishell.h"

// int		searsh_variable_name(char *var, char *searsh, unsigned int position)
// {
// 	int	i;
//
// 	i = 0;
// 	if (position == START)
// 	{
// 		while ((var[i] != '\0' && var[i] == searsh[i])
// 			&& (var[i] != '=' && searsh[i] != '='))
// 			i++;
// 		if (i == 0)
// 			return (FALSE);
// 		else if (var[i] != '=' && searsh[i] != '=')
// 			return (TRUE);
// 		else if (searsh[i] == '\0')
// 			return (TRUE);
// 	}
// 	return (TRUE);
// }

t_envp	*locate_node(t_envp *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->located != 1)
		lst = lst->next;
	return (lst);
}

void	add_variable(t_envp **env_lst, char *var, char *val)
{
	ft_lstadd_back(env_lst, ft_lstnew(var, val, 0));
}

void	export_with_value(t_envp **env_lst, char *var, char *val, int exist)
{
	t_envp	*tmp;

	tmp = locate_node(*env_lst);
	if (tmp == NULL)
		tmp = ft_lstlast(*env_lst);
	if (exist == 1)
	{
		free(tmp->value);
		tmp->value = ft_strdup(val);
		tmp->includes_in_expt = 0;
	}
	else
	{
		add_variable(env_lst, ft_strdup(var), ft_strdup(val));
		sort_lst(env_lst);
	}
}

void	export_no_value(t_envp **env_lst, char *var, char *val, int exist)
{
	t_envp	*tmp;

	tmp = locate_node(*env_lst);
	if (tmp == NULL)
		tmp = ft_lstlast(*env_lst);
	if (exist == 1)
	{
		free(tmp->value);
		if (val == NULL)
			tmp->value = ft_strdup("");
		else
			tmp->value = ft_strdup(val);
		tmp->includes_in_expt = 0;
	}
	else
	{
		add_variable(env_lst, ft_strdup(var), ft_strdup(val));
		sort_lst(env_lst);
	}
}

void	export_no_eqaul_sign(t_envp **env_lst, char *var, char *val, int exist)
{
	t_envp	*tmp;

	tmp = NULL;
	if (exist == 0)
	{
		add_variable(env_lst, ft_strdup(var), ft_strdup(val));
		tmp = ft_lstlast(*env_lst);
		tmp->includes_in_expt = 1;
		sort_lst(env_lst);
	}
}

void	export_with_plus_equal_signs(t_envp **env_lst, char *var, char *val, int exist)
{
	t_envp	*tmp;
	char	*str;

	tmp = locate_node(*env_lst);
	if (tmp == NULL)
		tmp = ft_lstlast(*env_lst);
	if (exist == 1)
	{
		str = tmp->value;
		tmp->value = ft_strjoin(tmp->value, ft_strdup(val));
		free(str);
		tmp->includes_in_expt = 0;
	}
	else
	{
		add_variable(env_lst, ft_strdup(var), ft_strdup(val));
		if (val == NULL)
		{
			tmp = ft_lstlast(*env_lst);
			tmp->includes_in_expt = 1;
		}
		sort_lst(env_lst);
	}
}

