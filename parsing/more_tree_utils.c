/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tree_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 02:28:49 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 02:30:04 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_ps(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		temp = ft_lstlast_ps(*lst);
		temp->next = new;
		new->prev = temp;
	}
}

t_tree	*new_tree_node_ps(t_list *nodes)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->commands = NULL;
	tree->redirection = NULL;
	tree->type = nodes->type;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

void	new_list_node_ps(t_list **new, char *content)
{
	t_list	*new_node;
	t_list	*tmp;

	tmp = NULL;
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	if (!(*new))
		*new = new_node;
	else
	{
		tmp = ft_lstlast_ps(*new);
		tmp->next = new_node;
	}
}

void	ft_lstclear_double(t_list **lst)
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}
