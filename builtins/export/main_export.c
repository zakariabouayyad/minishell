/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:55:27 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/24 08:27:31 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_export(t_envp *env_lst)
{
	int	error;

	error = errno;
	while (env_lst != NULL)
	{
		if (env_lst->shlvl_var != 0)
		{
			printf("declare -x %s=\"%d\"\n", env_lst->variable,
				env_lst->shlvl_var);
		}
		else if (env_lst->value == NULL)
			printf("declare -x %s\n", env_lst->variable);
		else
		{
			printf("declare -x %s=\"%s\"\n", env_lst->variable,
				env_lst->value);
		}
		env_lst = env_lst->next;
	}
	g_status = (error != errno);
}

static void	execute_exprot_handl_input(t_exp *e, t_list **lst)
{
	e->i = FALSE;
	e->str = NULL;
	e->str = joining_input(lst);
	e->var = var_clean_content(e->str);
	e->val = val_clean_content(ft_strchr(e->str, '='));
	if (*lst && (*lst)->content && e->val == NULL && (*lst)->content[0] == '\0')
		e->val = ft_strdup("");
}

static void	execute_exprot_handl_type_id(t_exp *e, t_list *lst)
{
	e->type = invalid_identifier_check(e->str);
	if (e->type == FALSE)
	{
		if (e->var != NULL)
			printf("minishell: export: `%s': not a valid identifier\n", e->var);
		g_status = 1;
	}
	else if (e->type == EXP_N_VAL && e->i == TRUE)
		e->type = EXP_W_VAL;
}

static int	execute_exprot_error_end_lst(t_list *lst)
{
	if (lst == NULL)
		return (1);
	return (0);
}

void	execute_exprot(t_envp **env_lst, t_list *lst)
{
	t_exp	e;

	if (env_lst && *env_lst && lst->next == NULL)
	{
		print_export(*env_lst);
		return ;
	}
	if (!lst->next)
		return ;
	lst = lst->next->next;
	while (lst != NULL)
	{
		if (!(lst->content[0] == ' ' && lst->content[1] == '\0'))
		{
			execute_exprot_handl_input(&e, &lst);
			execute_exprot_handl_type_id(&e, lst);
			if (e.var && !(e.var[0] == '_' && e.var[1] == '\0'))
				ft_setenv(e.var, e.val, env_lst, e.type);
			(free(e.str), e.str = NULL);
			(ft_free(e.var, e.val, NULL, NULL), e.i = FALSE);
			if (execute_exprot_error_end_lst(lst))
				return ;
		}
		lst = lst->next;
	}
}
