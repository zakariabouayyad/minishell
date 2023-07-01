/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:44:25 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 12:44:28 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*new_token_parentheses(char *str, t_tokens token)
{
	t_list	*token_node;

	token_node = malloc(sizeof(t_list));
	if (!token_node)
		return (NULL);
	token_node->content = ft_strdup(str);
	token_node->type = token;
	token_node->next = NULL;
	token_node->prev = NULL;
	return (token_node);
}

t_list	*inside_parentheses(t_list **nodes)
{
	t_list	*new;
	t_list	*res;
	int		num_par;

	res = NULL;
	num_par = 1;
	*nodes = (*nodes)->next;
	while (*nodes)
	{
		if ((*nodes)->type == OPEN_PARENTHESIS)
			num_par++;
		else if ((*nodes)->type == CLOSE_PARENTHESIS)
			num_par--;
		if (num_par == 0)
		{
			*nodes = (*nodes)->next;
			break ;
		}
		new = new_token_parentheses((*nodes)->content, (*nodes)->type);
		ft_lstadd_back_double(&res, new);
		*nodes = (*nodes)->next;
	}
	return (res);
}

void	make_nodes(t_list **nodes, t_list *new, t_tree *tree)
{
	if (is_redirection((*nodes)->type))
	{
		new = ft_lstnew_ps((*nodes)->content, (*nodes)->type);
		ft_lstadd_back_ps(&tree->redirection, new);
		(*nodes) = (*nodes)->next;
		new = ft_lstnew_ps((*nodes)->content, (*nodes)->type);
		ft_lstadd_back_ps(&tree->redirection, new);
	}
	else
	{
		new = ft_lstnew_ps((*nodes)->content, (*nodes)->type);
		ft_lstadd_back_ps(&tree->commands, new);
	}
}

t_tree	*cmd_node_ps(t_list **nodes)
{
	t_tree	*tree;
	t_list	*new;
	t_list	*subnodes;
	t_list	*tmp;

	tree = new_tree_node_ps((*nodes));
	if ((*nodes)->type == OPEN_PARENTHESIS)
	{
		free(tree);
		subnodes = inside_parentheses(nodes);
		tmp = subnodes;
		tree = and_or_case_ps(&subnodes);
		free_tlist(tmp);
	}
	else
	{	
		while ((*nodes) && (*nodes)->type != PIPE
			&& (*nodes)->type != AND && (*nodes)->type != OR)
		{
			make_nodes(nodes, new, tree);
			if ((*nodes))
				(*nodes) = (*nodes)->next;
		}
	}
	return (tree);
}

t_tree	*operator_node_ps(t_list **nodes)
{
	t_tree	*tree;
	t_list	*new;

	tree = new_tree_node_ps((*nodes));
	new = ft_lstnew_ps((*nodes)->content, (*nodes)->type);
	ft_lstadd_back_ps(&tree->commands, new);
	(*nodes) = (*nodes)->next;
	return (tree);
}
