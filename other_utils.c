/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 06:13:22 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/24 07:26:58 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_2(t_list *lst)
{
	int	count;

	count = 0;
	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		if (!(lst->content[0] == ' ' && lst->content[1] == '\0'))
			count++;
		lst = lst->next;
	}
	return (count);
}

char	**list_to_string(t_list *head)
{
	int		len;
	int		i;
	char	**array;
	t_list	*current;

	i = 0;
	len = 0;
	current = head;
	len = ft_lstsize_2(head);
	array = (char **)malloc((len + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (current)
	{
		if (!(current->content[0] == ' ' && current->content[1] == '\0'))
		{
			array[i] = ft_strdup(current->content);
			i++;
		}
		current = current->next;
	}
	array[i] = NULL;
	return (array);
}

char	**transfom_env_lst(t_envp *env_lst)
{
	char	**envp;
	char	*tmp;
	int		size;
	int		i;

	if (!env_lst)
		return (NULL);
	i = 0;
	tmp = NULL;
	size = ft_lstsize_envp(env_lst);
	envp = (char **)malloc((size + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	while (env_lst)
	{
		tmp = ft_strjoin(env_lst->variable, "=");
		envp[i] = ft_strjoin(tmp, env_lst->value);
		if (tmp)
			(free(tmp), tmp = NULL);
		env_lst = env_lst->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

t_list	*ft_lstlast_list(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstjoin(t_list *lst, t_list *wc_lst)
{
	t_list	*tmp_prev;
	t_list	*tmp_next;

	if (!lst || !wc_lst)
		return ;
	tmp_prev = NULL;
	tmp_next = NULL;
	if (lst->prev)
		tmp_prev = lst->prev;
	if (lst->next)
		tmp_next = lst->next;
	if (lst && lst->content)
		(free(lst->content), lst->content = NULL);
	if (lst)
		(free(lst), lst = NULL);
	if (tmp_prev)
		if (tmp_prev->next)
			tmp_prev->next = wc_lst;
	if (tmp_next)
	{
		tmp_next->prev = ft_lstlast(wc_lst);
		tmp_next->prev->next = tmp_next;
	}
}
