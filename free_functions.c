/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 06:06:50 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/24 07:31:51 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list *head)
{
	t_list	*current;
	t_list	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}

void	free_tlist(t_list *head)
{
	t_list	*current;
	t_list	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}

void	free_tree(t_tree *tree)
{
	if (tree == NULL)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	if (tree->commands)
		free_tlist(tree->commands);
	if (tree->redirection)
		free_tlist(tree->redirection);
	if (tree)
		free(tree);
}
