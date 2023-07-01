/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:55:36 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/24 07:24:19 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	export_with_value(t_envp **env_lst, char *var, char *val, int exist)
{
	t_envp	*tmp;

	tmp = locate_node(*env_lst);
	if (tmp == NULL)
		tmp = ft_lstlast_envp(*env_lst);
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

static void	export_no_value(t_envp **env_lst, char *var, char *val, int exist)
{
	t_envp	*tmp;

	tmp = locate_node(*env_lst);
	if (tmp == NULL)
		tmp = ft_lstlast_envp(*env_lst);
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

static void	export_no_eqaul_sign(t_envp **env_lst, char *var, char *val,
	int exist)
{
	t_envp	*tmp;

	tmp = NULL;
	if (exist == 0)
	{
		add_variable(env_lst, ft_strdup(var), ft_strdup(val));
		tmp = ft_lstlast_envp(*env_lst);
		tmp->includes_in_expt = 1;
		sort_lst(env_lst);
	}
}

static void	export_with_plus_equal_signs(t_envp **env_lst, char *var,
	char *val, int exist)
{
	t_envp	*tmp;
	char	*str;

	tmp = locate_node(*env_lst);
	if (tmp == NULL)
		tmp = ft_lstlast_envp(*env_lst);
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
			tmp = ft_lstlast_envp(*env_lst);
			tmp->includes_in_expt = 1;
		}
		sort_lst(env_lst);
	}
}

void	ft_setenv(char *var, char *val, t_envp **env_lst, int type)
{
	t_exp	e;

	e.i = -1;
	while (var[++e.i])
		if (var[e.i] == '+' || var[e.i] == '=')
			var[e.i++] = '\0';
	e.num = var_existens_in_env_lst(*env_lst, var);
	if (type == EXP_W_VAL)
		export_with_value(env_lst, var, val, e.num);
	else if (type == EXP_N_VAL)
		export_no_value(env_lst, var, val, e.num);
	else if (type == EXP_N_EQU)
		export_no_eqaul_sign(env_lst, var, val, e.num);
	else if (type == EXP_W_P_EQU)
		export_with_plus_equal_signs(env_lst, var, val, e.num);
}
