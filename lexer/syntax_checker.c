/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:44:51 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 12:58:53 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	close_par_syntax(t_list *tokens)
{
	if (!tokens->prev || (tokens->prev
			&& tokens->prev->type != WORD
			&& tokens->prev->type != D_QUOTED
			&& tokens->prev->type != S_QUOTED
			&& tokens->prev->type != DOLLAR
			&& tokens->prev->type != CLOSE_PARENTHESIS)
		|| (tokens->next
			&& tokens->next->type != AND
			&& tokens->next->type != OR
			&& tokens->next->type != PIPE
			&& tokens->next->type != CLOSE_PARENTHESIS))
		return (false);
	else
		return (true);
}

bool	open_par_syntax(t_list *tokens)
{
	if (!tokens->next
		|| (tokens->prev
			&& tokens->prev->type != AND
			&& tokens->prev->type != OR
			&& tokens->prev->type != PIPE
			&& tokens->prev->type != OPEN_PARENTHESIS)
		|| (tokens->next
			&& tokens->next->type != WORD
			&& tokens->next->type != D_QUOTED
			&& tokens->next->type != S_QUOTED
			&& tokens->next->type != DOLLAR
			&& tokens->next->type != OPEN_PARENTHESIS
			&& !is_redirection(tokens->next->type)))
		return (false);
	else
		return (true);
}

bool	operators_syntax(t_list *tokens)
{
	if ((!tokens->prev || !tokens->next)
		|| (tokens->next
			&& tokens->next->type != WORD
			&& tokens->next->type != D_QUOTED
			&& tokens->next->type != S_QUOTED
			&& tokens->next->type != DOLLAR
			&& !is_redirection(tokens->next->type)
			&& tokens->next->type != OPEN_PARENTHESIS)
		|| (tokens->prev && (tokens->prev->type != WORD
				&& tokens->prev->type != DOLLAR
				&& tokens->prev->type != D_QUOTED
				&& tokens->prev->type != S_QUOTED
				&& tokens->prev->type != CLOSE_PARENTHESIS)))
		return (false);
	else
		return (true);
}

bool	syntax_conitions(t_list *tokens)
{
	if (tokens->type == PIPE || tokens->type == OR || tokens->type == AND)
	{
		if (operators_syntax(tokens) == false)
			return (false);
	}
	else if (is_redirection(tokens->type))
	{
		if (!tokens->next || (tokens->next
				&& tokens->next->type != WORD && tokens->next->type != DOLLAR
				&& tokens->next->type != D_QUOTED
				&& tokens->next->type != S_QUOTED))
			return (false);
	}
	else if (tokens->type == OPEN_PARENTHESIS)
	{
		if (open_par_syntax(tokens) == false)
			return (false);
	}
	else if (tokens->type == CLOSE_PARENTHESIS)
	{
		if (close_par_syntax(tokens) == false)
			return (false);
	}
	return (true);
}

bool	syntax_checker_ps(t_list *tokens)
{
	t_list	*tmp;
	int		flag_par;

	flag_par = 0;
	tmp = tokens;
	if (parentheses_closed(tmp) == false)
		return (false);
	while (tokens)
	{
		if (syntax_conitions(tokens) == false)
			return (false);
		tokens = tokens->next;
	}
	return (true);
}
