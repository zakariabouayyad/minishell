#include "../minishell.h"

bool	double_checker_ps(char *input)
{
	int	i = 0;
	int	double_quote = 0;
	int	single_quote = 0;
	int	par = 0;

	while(input[i])
	{
		if (input[i] == '$' && (!input[i + 1] || input[i + 1] == ' '))
			return (false);
		else if (input[i] == '"')
			double_quote++;
		else if (input[i] == '\'')
			single_quote++;
		else if (input[i] == '(')
		{
			par++;
			if (input[i] == '(' && input[i + 1] == ')')
				return (false);
		}
		else if (input[i] == ')')
			par--;
		i++;
	}
	if ((double_quote % 2 != 0) || (single_quote % 2 != 0) || (par != 0))
		return (false);
	return (true);
}

bool	syntax_checker_ps(t_lexer *tokens)
{
	int	flag_par;

	flag_par = 0;
	while (tokens)
	{
		if (tokens->type == PIPE || tokens->type == OR || tokens->type == AND)
		{
			if (!tokens->prev || !tokens->next || (tokens->next && tokens->next->type != WORD && tokens->next->type != OPEN_PARENTHESIS) || (tokens->prev && (tokens->prev->type != WORD && tokens->prev->type != CLOSE_PARENTHESIS)))
				return (false);
		}
		else if (tokens->type == INPUT || tokens->type == OUTPUT || tokens->type == OUTPUT_APPEND)
		{
			if (!tokens->next || (tokens->next && tokens->next->type != WORD))
				return (false);
		}
		else if (tokens->type == HERE_DOC)
		{
			if (!tokens->next || (tokens->next && tokens->next->type != WORD))/*add word as limiter and if there is double quotes it should be expanded*/
				return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}

int	is_word(int token)
{
	if (token == WORD || token == D_QUOTED || token == S_QUOTED
		|| token == DOLLAR)
		return (1);
	return (0);
}

t_lexer	*remove_node_ps(t_lexer *head, int space)
{
	t_lexer	*current;
	t_lexer	*tmp;

	current = head;
	tmp = NULL;
	while (current)
	{
		if (current->type == space
			&& (current->next && !is_word(current->next->type)
			|| current->prev && !is_word(current->prev->type)))
		{
			/*store the next node before freeing the current node*/
			tmp = current->next;
			/*if the current node is the head*/
			if (current == head)
				head = current->next;
			/*unlink the node from the list*/
			if (current->prev)
				current->prev->next = tmp;
			if (tmp)
				current->next->prev = current->prev;
			// free(current);
			/*move to the next node*/
			current = tmp;
		}
		else if (current->type == space && !current->next)
		{
			/*store the next node before freeing the current node*/
			tmp = current->next;
			/*if the current node is the head*/
			if (current == head)
				head = current->next;
			/*unlink the node from the list*/
			if (current->prev)
				current->prev->next = tmp;
			if (tmp)
				current->next->prev = current->prev;
			// free(current);
			/*move to the next node*/
			current = tmp;
		}
		else
		{
			current = current->next;
		}
	}
	return (head);
}
