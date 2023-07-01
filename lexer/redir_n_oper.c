/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_n_oper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:22:46 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/22 00:57:53 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_output(char *input, int i, t_list **head, t_list **tail)
{
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
		{
			add_token(head, tail, ">>", OUTPUT_APPEND);
			return (2);
		}
		else
		{
			add_token(head, tail, ">", OUTPUT);
			return (1);
		}
	}
	return (0);
}

int	handle_input(char *input, int i, t_list **head, t_list **tail)
{
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			add_token(head, tail, "<<", HERE_DOC);
			return (2);
		}
		else
		{
			add_token(head, tail, "<", INPUT);
			return (1);
		}
	}
	return (0);
}

int	hanele_pipe_n_or(char *input, int i, t_list **head, t_list **tail)
{
	if (input[i] == '|')
	{
		if (input[i + 1] == '|')
		{
			add_token(head, tail, "||", OR);
			return (2);
		}
		else
		{
			add_token(head, tail, "|", PIPE);
			return (1);
		}
		return (0);
	}
	return (0);
}

int	hanele_and(char *input, int i, t_list **head, t_list **tail)
{
	if (input[i] == '&')
	{
		if (input[i + 1] == '&')
		{
			add_token(head, tail, "&&", AND);
			return (2);
		}
	}
	return (0);
}
