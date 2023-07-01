/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:22:43 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 02:15:10 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_open_parenthesis(char *input, t_list **head, t_list **tail)
{
	add_token(head, tail, "(", OPEN_PARENTHESIS);
	return (1);
}

int	handle_close_parenthesis(char *input, t_list **head, t_list **tail)
{
	add_token(head, tail, ")", CLOSE_PARENTHESIS);
	return (1);
}

int	handle_white_space(t_list **head, t_list **tail, char *str)
{
	int	i;

	i = 0;
	while (is_white_space(str[i]))
		i++;
	add_token(head, tail, " ", WHITE_SPACE);
	return (i);
}

int	is_redirection(int tokens)
{
	if (tokens == HERE_DOC || tokens == INPUT
		|| tokens == OUTPUT || tokens == OUTPUT_APPEND)
		return (1);
	return (0);
}
