/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:45:53 by zbouayya          #+#    #+#             */
/*   Updated: 2023/05/26 21:55:06 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree *pipe_case_ps(t_lexer **nodes)
{
	t_tree	*tree;
	t_tree	*tmp;

	tree = cmd_node_ps(nodes);
	while ((*nodes) != NULL && (*nodes)->type == PIPE)
	{
		tmp = tree;
		tree = operator_node_ps(nodes);
		tree->left = tmp;
		tree->right = cmd_node_ps(nodes);
	}
	return (tree);
}

t_tree	*and_or_case_ps(t_lexer **nodes)
{
	t_tree	*tree;
	t_tree	*tmp;

	tree = pipe_case_ps(nodes);
	while ((*nodes) != NULL
			&& ((*nodes)->type == OR || (*nodes)->type == AND))
	{
		tmp = tree;
		tree = operator_node_ps(nodes);
		tree->left = tmp;
		tree->right = pipe_case_ps(nodes);
	}
	return (tree);
}

t_tree	*build_tree_ps(t_lexer *nodes)
{
	if (!nodes)
		return (NULL);
    return (and_or_case_ps(&nodes));
}
