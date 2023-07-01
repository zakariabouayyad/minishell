/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:07:20 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 02:18:37 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_word(int token)
{
	if (token == WORD || token == D_QUOTED || token == S_QUOTED
		|| token == DOLLAR)
		return (1);
	return (0);
}

t_list	*remove_node_ps(t_list *head, int space)
{
	t_list	*current;
	t_list	*tmp;

	current = head;
	tmp = NULL;
	while (current)
	{
		if (current->type == space && (current->next
				&& !is_word(current->next->type) || current->prev
				&& !is_word(current->prev->type) || !current->next))
		{
			tmp = current->next;
			if (current == head)
				head = current->next;
			if (current->prev)
				current->prev->next = tmp;
			if (tmp)
				current->next->prev = current->prev;
			(free(current->content), free(current));
			current = tmp;
		}
		else
			current = current->next;
	}
	return (head);
}

bool	double_checker_ps(char *input)
{
	int	i;
	int	double_quote;
	int	single_quote;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	if (input[0] == ')' && input[1] == '(')
		return (false);
	while (input[i])
	{
		if (input[i] == ';' && input[i + 1] == ';')
			return (false);
		if (input[i] == '"')
			double_quote++;
		else if (input[i] == '\'')
			single_quote++;
		i++;
	}
	if ((double_quote % 2 != 0) || (single_quote % 2 != 0))
		return (false);
	return (true);
}

bool	parentheses_closed(t_list *head)
{
	t_list	*current;
	int		open_count;

	open_count = 0;
	current = head;
	while (current)
	{
		if (current->type == OPEN_PARENTHESIS)
			open_count++;
		else if (current->type == CLOSE_PARENTHESIS)
			open_count--;
		current = current->next;
	}
	if (open_count != 0)
		return (false);
	else
		return (true);
}
