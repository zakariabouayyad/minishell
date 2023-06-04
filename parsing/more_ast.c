/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:44:25 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/04 20:16:19 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_tree *cmd_node_ps(t_lexer **nodes)
// {
// 	t_tree	*tree;
// 	t_list	*new;
// 	t_lexer	*par;
// 	t_lexer	*par2;

// 	tree = new_tree_node_ps((*nodes));
// 	par2 = ft_lstnew_double((*nodes)->value);
// 	par2 = NULL;
// 	if ((*nodes)->type == OPEN_PARENTHESIS)
// 	{
// 	    (*nodes) = (*nodes)->next;
// 	    while ((*nodes) && (*nodes)->type != CLOSE_PARENTHESIS)
// 	    {
// 	        if ((*nodes)->type != CLOSE_PARENTHESIS)
// 			{
// 	            par = ft_lstnew_double((*nodes)->value);
// 	            ft_lstadd_back_double(&par2, par);
// 	        }
// 	        (*nodes) = (*nodes)->next;
// 	    }
// 		(*nodes) = (*nodes)->next;
// 		return (and_or_case_ps(&par2));
// 	}
// 	while ((*nodes) && (*nodes)->type != PIPE && (*nodes)->type != AND && (*nodes)->type != OR)
// 	{
// 		if ((*nodes)->type == INPUT || (*nodes)->type == OUTPUT || (*nodes)->type == OUTPUT_APPEND || (*nodes)->type == HERE_DOC)
// 		{
// 			new = ft_lstnew_ps((*nodes)->value);
// 			ft_lstadd_back_ps(&tree->redirection, new);
// 			(*nodes) = (*nodes)->next;
// 			new = ft_lstnew_ps((*nodes)->value);
// 			ft_lstadd_back_ps(&tree->redirection, new);
// 		}
// 		else
// 		{
// 			new = ft_lstnew_ps((*nodes)->value);
// 			ft_lstadd_back_ps(&tree->commands, new);
// 		}
// 		(*nodes) = (*nodes)->next;
// 	}
// 	return (tree);
// }

t_tree *cmd_node_ps(t_lexer **nodes)
{
	t_tree	*tree;
	t_list	*new;
	t_lexer	*new_double;
	t_lexer	*tmp_double;

	new_double = NULL;
	tree = new_tree_node_ps((*nodes));
	if ((*nodes)->type == OPEN_PARENTHESIS)
	{
		(*nodes) = (*nodes)->next;
		while ((*nodes) && (*nodes)->type != CLOSE_PARENTHESIS)
		{
			tmp_double = ft_lstnew_double((*nodes)->value);
			tmp_double->type = (*nodes)->type;
			ft_lstadd_back_double(&new_double, tmp_double);
			(*nodes) = (*nodes)->next;
		}
		// (*nodes) = (*nodes)->next;
		return (and_or_case_ps(&new_double));
	}
	while ((*nodes) && (*nodes)->type != PIPE && (*nodes)->type != AND && (*nodes)->type != OR)
	{
		if ((*nodes)->type == INPUT || (*nodes)->type == OUTPUT
			|| (*nodes)->type == OUTPUT_APPEND || (*nodes)->type == HERE_DOC)
		{
			new = ft_lstnew_ps((*nodes)->value);
			ft_lstadd_back_ps(&tree->redirection, new);
			(*nodes) = (*nodes)->next;
			new = ft_lstnew_ps((*nodes)->value);
			ft_lstadd_back_ps(&tree->redirection, new);
		}
		else
		{
			new = ft_lstnew_ps((*nodes)->value);
			ft_lstadd_back_ps(&tree->commands, new);
		}
		(*nodes) = (*nodes)->next;
	}
	return (tree);
}

t_tree *operator_node_ps(t_lexer **nodes)
{
	t_tree	*tree;
	t_list	*new;

	tree = new_tree_node_ps((*nodes));
	new = ft_lstnew_ps((*nodes)->value);
	ft_lstadd_back_ps(&tree->commands, new);
	(*nodes) = (*nodes)->next;
	return (tree);
}
