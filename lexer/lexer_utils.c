/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:22:34 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 10:34:47 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*new_token_ps(char *str, t_tokens token)
{
	t_list	*token_node;

	token_node = malloc(sizeof(t_list));
	token_node->content = ft_strdup(str);
	token_node->type = token;
	token_node->next = NULL;
	token_node->prev = NULL;
	if ((token == WORD || token == S_QUOTED
			|| token == D_QUOTED || token == DOLLAR))
		free(str);
	return (token_node);
}

void	add_token(t_list **head, t_list **tail, char *token, t_tokens type)
{
	t_list	*token_node;

	token_node = new_token_ps(token, type);
	if (*tail == NULL)
	{
		*head = token_node;
		*tail = token_node;
	}
	else
	{
		(*tail)->next = token_node;
		token_node->prev = *tail;
		*tail = token_node;
	}
}

int	is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f' || c == '\n')
		return (1);
	return (0);
}

int	not_and(char c, char c1)
{
	if (c == '&' && c1 != '&')
		return (1);
	return (0);
}

int	handle_status(char *input, int i, t_list **head, t_list **tail)
{
	if (input[i] == '$')
	{
		if (input[i + 1] == '?')
		{
			add_token(head, tail, ft_strdup("$?"), DOLLAR);
			return (2);
		}
	}
	return (0);
}
