/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_strings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:22:28 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 02:24:17 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_word(char c)
{
	if (c == '\'' || c == '\"' || c == '<' || c == '>' || c == '|'
		|| c == '(' || c == ')' || c == '$'
		|| is_white_space(c) || c == '\n' || c == '\0')
		return (1);
	else
		return (0);
}

int	handle_word(t_list **head, t_list **tail, int i, char *input)
{
	int		end;
	int		start;
	int		word_len;
	char	*word;

	start = i;
	while (input[i] && !not_word(input[i]))
		i++;
	end = i;
	word_len = end - start;
	word = ft_substr(input, start, word_len);
	add_token(head, tail, word, WORD);
	return (word_len);
}

int	handle_dollar(char *input, int i, t_list **head, t_list **tail)
{
	int		end;
	int		word_len;
	int		start;
	char	*word;

	start = i;
	i++;
	while ((input[i]) && input[i] != '$'
		&& (input[i] == '_' || ft_isalpha(input[i]) || ft_isdigit(input[i])))
		i++;
	end = i;
	word_len = end - start;
	word = ft_substr(input, start, word_len);
	add_token(head, tail, word, DOLLAR);
	return (word_len);
}

int	handle_single_quoted(char *input, int i, t_list **head, t_list **tail)
{
	int		end;
	int		start;
	int		word_len;
	char	quote_char;
	char	*word;

	quote_char = input[i];
	i++;
	start = i;
	while (input[i] && input[i] != quote_char)
		i++;
	if (input[i] == '\0')
		return (1);
	else
	{
		end = i;
		word_len = end - start;
		word = ft_substr(input, start, word_len);
		add_token(head, tail, word, S_QUOTED);
		return (word_len + 2);
	}
	return (0);
}

int	handle_double_quoted(char *input, int i, t_list **head, t_list **tail)
{
	int		end;
	int		start;
	int		word_len;
	char	quote_char;
	char	*word;

	quote_char = input[i];
	i++;
	start = i;
	while (input[i] && input[i] != quote_char)
		i++;
	if (input[i] == '\0')
		return (1);
	else
	{
		end = i;
		word_len = end - start;
		word = ft_substr(input, start, word_len);
		add_token(head, tail, word, D_QUOTED);
		return (word_len + 2);
	}
	return (0);
}
