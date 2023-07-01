/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:49:13 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/21 20:24:43 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	fist_printing(t_envp *env_lst, t_envp *tmp, int list_size, int loc)
{
	while (loc <= list_size)
	{
		tmp = env_lst;
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
	return (loc);
}

static void	second_printing(t_envp *tmp)
{	
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

int	print_envp(t_envp **env_lst, int list_size)
{
	t_envp		*tmp;
	int			loc;
	int			error;
	int			size;

	if (!env_lst || !(*env_lst))
		return (1);
	error = errno;
	size = ft_lstsize_envp(*env_lst);
	loc = fist_printing(*env_lst, tmp, list_size, 1);
	tmp = *env_lst;
	while (tmp && loc-- > 1)
		tmp = tmp->next;
	second_printing(tmp);
	if (error != errno)
		return (1);
	return (0);
}
