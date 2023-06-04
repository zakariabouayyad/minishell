/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:45:56 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/04 19:54:50 by zbouayya         ###   ########.fr       */
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

t_lexer	*ft_lstnew_double(char *content)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (new == NULL)
		return (NULL);
	new->value = strdup(content);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_double(t_lexer **lst, t_lexer *new)
{
	t_lexer	*temp;

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

t_list	*ft_lstnew_ps(char *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = strdup(content);
	new->next = NULL;
	return (new);
}

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
	}
}

// t_list	*newnode_ps(char *data, t_tokens type)
// {
// 	t_tree	*new;

// 	new = (t_tree *)malloc(sizeof(t_tree));
// 	if (!new)
// 		return (NULL);
// 	if (type == INPUT || type == OUTPUT || type == OUTPUT_APPEND || type == HERE_DOC)
// 	{
// 		new->redirection = (t_list *)malloc(sizeof(t_list));
// 		new->redirection->content = data;
// 	}
// 	else
// 	{
// 		new->commands = (t_list *)malloc(sizeof(t_list));
// 		new->commands->content = data;
// 	}
// 	new->type = type;
// 	new->left = NULL;
// 	new->right = NULL;
// 	return (new);
// }

// t_tree	*new_tree_node_ps(t_tree *tree, t_lexer *nodes)/* looks correct to me */
// {
// 	tree = (t_tree *)malloc(sizeof(t_tree));
// 	if (!tree)
// 		return (NULL);
// 	if (nodes->type == INPUT || nodes->type == OUTPUT || nodes->type == OUTPUT_APPEND || nodes->type == HERE_DOC)
// 		new_list_node_ps(&tree->redirection, nodes->value);
// 	else
// 		new_list_node_ps(&tree->commands, nodes->value);
// 	tree->type = nodes->type;
// 	tree->left = NULL;
// 	tree->right = NULL;
// 	return (tree);
// }

t_tree	*new_tree_node_ps(t_lexer *nodes)/* looks correct to me */
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
	
	tree->str = NULL;/*for export*/
	return (tree);
}

void	new_list_node_ps(t_list **new, char *content)/* correct */
{
	t_list *new_node;
	t_list *tmp = NULL;

    new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return;
    new_node->content = strdup(content);
    new_node->next = NULL;

    if (!(*new))
        *new = new_node;
    else
    {
        tmp = ft_lstlast_ps(*new);
        tmp->next = new_node;
    }
}

void ft_lstclear_double(t_lexer **lst)
{
	t_lexer *current = *lst;
	while (current != NULL)
	{
		t_lexer *next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*lst = NULL;
}