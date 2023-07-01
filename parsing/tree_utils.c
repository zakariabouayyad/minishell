/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:45:56 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 02:29:51 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize_ps(t_list *lst)
{
	int	count;

	count = 0;
	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

t_list	*ft_lstlast_ps(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*ft_lstnew_double(char *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = ft_strdup(content);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_double(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}

t_list	*ft_lstnew_ps(char *content, int type)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = ft_strdup(content);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
