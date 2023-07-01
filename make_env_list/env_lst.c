/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 06:10:33 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/24 10:18:01 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_special_env_list(t_envp **env_lst)
{
	ft_lstadd_back_envp(env_lst, ft_lstnew_envp(ft_strdup("OLDPWD"), NULL, 0));
	(*env_lst)->includes_in_expt = 1;
	ft_lstadd_back_envp(env_lst, ft_lstnew_envp(ft_strdup("PWD"),
			getcwd(NULL, PATH_MAX), 0));
	ft_lstadd_back_envp(env_lst, ft_lstnew_envp(ft_strdup("SHLVL"),
			ft_strdup("1"), 1));
}

void	add_to_env_list(t_envp **env_lst, char *envp, t_utils *x, int shlvl)
{
	if (shlvl == 0 && ft_strnstr(envp, "SHLVL=", 6) != NULL)
	{
		shlvl = ft_atoi(&envp[6]) + 1;
		ft_lstadd_back_envp(env_lst, ft_lstnew_envp(x->tmp, ft_itoa(shlvl), shlvl));
	}
	else
		ft_lstadd_back_envp(env_lst, ft_lstnew_envp(x->tmp, ft_strdup(x->tmp1), 0));
}

void	indexing_env_order(t_envp **lst)
{
	t_envp	*tmp;
	int		i;

	if (!lst)
		return ;
	i = 1;
	tmp = *lst;
	while (tmp)
	{
		tmp->env_order = i;
		tmp = tmp->next;
		i++;
	}
}

void	make_env_list(char *envp[], t_envp **env_lst)
{
	t_utils			x;
	unsigned int	size;
	unsigned int	i;
	unsigned int	shlvl;

	i = 0;
	shlvl = 0;
	if (envp == NULL || envp[i] == NULL)
		make_special_env_list(env_lst);
	while (envp[i] != NULL)
	{
		x.tmp = ft_substr(envp[i], 0, (int)(ft_strchr(envp[i], '=') - envp[i]));
		x.tmp1 = getenv(x.tmp);
		add_to_env_list(env_lst, envp[i], &x, shlvl);
		i++;
	}
	indexing_env_order(env_lst);
	indexing(env_lst);
	sort_lst(env_lst);
	indexing(env_lst);
}
