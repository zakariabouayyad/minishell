/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:55:14 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/20 05:28:01 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	ft_lstadd_back_envp(env_lst, ft_lstnew_envp(var, val, 0));
}

static int	searsh_valiable(char *var, char *searsh, int len)
{
	int	i;

	i = 0;
	while (i < len && var[i] == searsh[i])
		i++;
	if (i != len)
		return (FALSE);
	else if (searsh[i] == '\0' && var[i] == '\0')
		return (TRUE);
	return (FALSE);
}

int	var_existens_in_env_lst(t_envp *env_lst, char *var)
{
	int	size;

	size = ft_strlen(var);
	while (env_lst != NULL)
	{
		env_lst->located = 0;
		if (searsh_valiable(env_lst->variable, var, size) == TRUE)
		{
			env_lst->located = 1;
			return (TRUE);
		}
		env_lst = env_lst->next;
	}
	return (FALSE);
}
