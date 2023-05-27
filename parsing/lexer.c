#include "minishell.h"

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
        }
        else if (input[i] == '&')
		{
            if (i + 1 < len && input[i + 1] == '&')
			{
                t_lexer *token_node = new_token_ps("&&", AND);
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
        }
		else if (input[i] == '<')
		{
            if (i + 1 < len && input[i + 1] == '<')
			{
                t_lexer *token_node = new_token_ps("<<", HERE_DOC);
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
                t_lexer *token_node = new_token_ps("<", INPUT);
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
        }
		else if (input[i] == '>')
		{
            if (i + 1 < len && input[i + 1] == '>')
			{
                t_lexer *token_node = new_token_ps(">>", OUTPUT_APPEND);
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
                t_lexer *token_node = new_token_ps(">", OUTPUT);
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
            t_lexer *token_node = new_token_ps(word, S_QUOTED);
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
            	t_lexer *token_node = new_token_ps(word, D_QUOTED);
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
            	i++; // Skip over quote character
			}
        }
		else if (input[i] == ' ')
		{
			while (i < len && input[i] == ' ')
				i++;
			t_lexer *token_node = new_token_ps(" ", WHITE_SPACE);
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
	    }
		else if (input[i] == '(')
		{
			while (i < len && input[i] == '(')
				i++;
			t_lexer *token_node = new_token_ps("(", OPEN_PARENTHESIS);
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
		}
		else if (input[i] == ')')
		{
			while (i < len && input[i] == ')')
				i++;
			t_lexer *token_node = new_token_ps(")", CLOSE_PARENTHESIS);
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
	        t_lexer *token_node = new_token_ps(word, DOLLAR);
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
	        t_lexer *token_node = new_token_ps(word, WORD);
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
	    }
		else
	        i++;
	}
	return (head);
}
