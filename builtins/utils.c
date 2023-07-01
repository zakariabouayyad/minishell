/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:16:03 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/21 21:52:16 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	indexing(t_envp **lst)
{
	t_envp	*tmp;
	int		i;

	if (!lst)
		return ;
	i = 1;
	tmp = *lst;
	while (tmp)
	{
		tmp->id = i;
		tmp = tmp->next;
		i++;
	}
}

void	move_node_to_location(t_swapnodes *swap, int x, int y)
{
	while (swap->currx && swap->currx->id != x)
	{
		swap->prevx = swap->currx;
		swap->currx = swap->currx->next;
	}
	while (swap->curry && swap->curry->id != y)
	{
		swap->prevy = swap->curry;
		swap->curry = swap->curry->next;
	}
}

void	swapnodes(t_envp **head, int x, int y)
{
	t_swapnodes	swap;

	swap.prevx = NULL;
	swap.currx = *head;
	swap.prevy = NULL;
	swap.curry = *head;
	if (x == y)
		return ;
	move_node_to_location(&swap, x, y);
	if (!swap.currx || !swap.curry)
		return ;
	if (swap.prevx)
		swap.prevx->next = swap.curry;
	else
		*head = swap.curry;
	if (swap.prevy)
		swap.prevy->next = swap.currx;
	else
		*head = swap.currx;
	swap.temp = swap.currx->next;
	swap.currx->next = swap.curry->next;
	swap.curry->next = swap.temp;
}

void	sort_lst(t_envp **env_lst)
{
	t_envp	*tmp;
	int		i;
	int		count;

	i = 0;
	count = ft_lstsize_envp(*env_lst);
	while (i < count - 1)
	{
		tmp = *env_lst;
		while (tmp && tmp->next != NULL)
		{
			if (ft_strcmp(tmp->variable, tmp->next->variable) > 0)
				swapnodes(env_lst, tmp->id, tmp->next->id);
			tmp = tmp->next;
		}
		i++;
	}
	indexing(env_lst);
}

void	ft_free(char *s1, char *s2, char **array1, char **array2)
{
	int	i;

	i = 0;
	if (s1)
		(free(s1), s1 = NULL);
	if (s2)
		(free(s2), s2 = NULL);
	if (array1)
	{
		while (array1[i] != NULL)
			(free(array1[i]), array1[i++] = NULL);
		(free(array1), array1 = NULL);
	}
	if (array2)
	{
		while (array2[i] != NULL)
			(free(array2[i]), array2[i++] = NULL);
		(free(array2), array2 = NULL);
	}
	return ;
}
