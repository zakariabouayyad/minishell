/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:44:46 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 07:40:08 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenizer_extra(t_list **head, t_list **tail, char *input, int i)
{
	if (input[i] == '(')
		i += handle_open_parenthesis(input, head, tail);
	else if (input[i] == ')')
		i += handle_close_parenthesis(input, head, tail);
	else if (input[i] == '$' && input[i + 1] == '?')
		i += handle_status(input, i, head, tail);
	else if (input[i] == '$')
		i += handle_dollar(input, i, head, tail);
	else if (!not_word(input[i]))
		i += handle_word(head, tail, i, input);
	else
		i++;
	return (i);
}

int	tokenizer(t_list **head, t_list **tail, char *input, int i)
{
	if (input[i] == '|')
		i += hanele_pipe_n_or(input, i, head, tail);
	else if (input[i] == '&' && input[i + 1] == '&')
		i += hanele_and(input, i, head, tail);
	else if (input[i] == '<')
		i += handle_input(input, i, head, tail);
	else if (input[i] == '>')
		i += handle_output(input, i, head, tail);
	else if (input[i] == '\'')
		i += handle_single_quoted(input, i, head, tail);
	else if (input[i] == '\"')
		i += handle_double_quoted(input, i, head, tail);
	else if (input[i] == ' ')
		i += handle_white_space(head, tail, input + i);
	else
		i = tokenizer_extra(head, tail, input, i);
	return (i);
}

t_list	*lexer(char *input)
{
	t_list	*head;
	t_list	*tail;
	int		i;
	int		len;

	head = NULL;
	tail = NULL;
	i = 0;
	len = ft_strlen(input);
	while (len > i && input[i])
		i = tokenizer(&head, &tail, input, i);
	return (head);
}
