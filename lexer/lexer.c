/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:44:46 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/02 17:44:47 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha_ps(int x)
{
	if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))
		return (1);
	else
		return (0);
}
int	ft_isdigit_ps(int x)
{
	if (x >= '0' && x <= '9')
		return (1);
	else
		return (0);
}
// Define a function to create a new lexer token
t_lexer *new_token_ps(char *str, t_tokens token)
{
    t_lexer *token_node = malloc(sizeof(t_lexer));
    token_node->value = str;
    token_node->type = token;
    // token_node->i = 0;
    token_node->next = NULL;
    token_node->prev = NULL;
    return (token_node);
}

t_lexer	*pipe_or_or(char *input, int i, t_lexer *head, t_lexer *tail)
{
	int len = strlen(input);
	
	if (i + 1 < len && input[i + 1] == '|')
	{
        t_lexer *token_node = new_token_ps("||", OR);
        if (tail == NULL)
		{
            head = token_node;
            tail = token_node;
        }
		else
		{
            tail->next = token_node;
			token_node->prev = tail;
            tail = token_node;
        }
        i += 2;
    }
	else
	{
        t_lexer *token_node = new_token_ps("|", PIPE);
        if (tail == NULL)
		{
            head = token_node;
            tail = token_node;
        }
		else
		{
            tail->next = token_node;
			token_node->prev = tail;
            tail = token_node;
        }
        i++;
    }
	return (head);
}


void add_token(t_lexer **head, t_lexer **tail, char *token, t_tokens type)
{
    t_lexer *token_node = new_token_ps(token, type);
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

// Define the lexer function
t_lexer *lexer(char *input)
{
	int		end;
	int		word_len;
	char	*word;
    t_lexer	*head = NULL;
    t_lexer	*tail = NULL;

	/*Using head and tail allows us to add nodes to the list efficiently without having to traverse the entire list every time*/
    int len = strlen(input);
    int i = 0;
    
    while (i < len)
	{
        // Check for tokens
        if (input[i] == '|')
		{
			// head = pipe_or_or(input, i, head, tail);
            if (i + 1 < len && input[i + 1] == '|')
			{
				add_token(&head, &tail, "||", OR);
                i += 2;
            }
			else
			{
				add_token(&head, &tail, "|", PIPE);
                i++;
            }
        }
        else if (input[i] == '&')
		{
            if (i + 1 < len && input[i + 1] == '&')
			{
				add_token(&head, &tail, "&&", AND);
                i += 2;
            }
        }
		else if (input[i] == '<')
		{
            if (i + 1 < len && input[i + 1] == '<')
			{
				add_token(&head, &tail, "<<", HERE_DOC);
                i += 2;
            }
			else
			{
				add_token(&head, &tail, "<", INPUT);
                i++;
            }
        }
		else if (input[i] == '>')
		{
            if (i + 1 < len && input[i + 1] == '>')
			{
				add_token(&head, &tail, ">>", OUTPUT_APPEND);
                i += 2;
            }
			else
			{
				add_token(&head, &tail, ">", OUTPUT);
                i++;
            }
	    }
		else if (input[i] == '\'')
		{
            // Read single quoted string
            char quote_char = input[i];
            i++;
            int start = i;
            while (i < len && input[i] != quote_char)
			{
                i++;
            }
            int end = i;
            int word_len = end - start;
            char *word = malloc(word_len + 1);
            memcpy(word, &input[start], word_len);
            word[word_len] = '\0';
				add_token(&head, &tail, word, S_QUOTED);
            i++; // Skip over quote character
        }
		else if (input[i] == '\"')
		{
            // Read double quoted string
            char quote_char = input[i];
            i++;
            int start = i;
            while (i < len && input[i] != quote_char)
                i++;
			if (input[i] == '\0')
				printf("syntax error\n");
			else
			{
            	int end = i;
            	int word_len = end - start;
            	char *word = malloc(word_len + 1);
            	memcpy(word, &input[start], word_len);
            	word[word_len] = '\0';
				add_token(&head, &tail, word, D_QUOTED);
            	i++; // Skip over quote character
			}
        }
		else if (input[i] == ' ')
		{
			while (i < len && input[i] == ' ')
				i++;
				add_token(&head, &tail, " ", WHITE_SPACE);
	    }
		else if (input[i] == '(')
		{
			while (i < len && input[i] == '(')
				i++;
			add_token(&head, &tail, "(", OPEN_PARENTHESIS);
		}
		else if (input[i] == ')')
		{
			while (i < len && input[i] == ')')
				i++;
			add_token(&head, &tail, ")", CLOSE_PARENTHESIS);
		}
		else if (input[i] == '$')
		{
	        // Read word
	        int start = i;
			i++;
	        while (i < len && (input[i] == '_' || ft_isalpha_ps(input[i]) || ft_isdigit_ps(input[i])))
	            i++;
	        end = i;
	        word_len = end - start;
	        word = (char *)malloc(word_len + 1);
	        memcpy(word, &input[start], word_len);
	        word[word_len] = '\0';
			add_token(&head, &tail, word, DOLLAR);
	    }
		else if (input[i] != ' ')
		{
	        // Read word
	        int start = i;
	        while (i < len && input[i] != ' ' && input[i] != '|' && input[i] != '<' && input[i] != '>' && input[i] != '\'' && input[i] != '"' && input[i] != '&' && input[i] != '$' && input[i] != '(' && input[i] != ')')
	            i++;
	        end = i;
	        word_len = end - start;
	        word = (char *)malloc(word_len + 1);
	        memcpy(word, &input[start], word_len);
	        word[word_len] = '\0';
			add_token(&head, &tail, word, WORD);
	    }
		else
	        i++;
	}
	return (head);
}
