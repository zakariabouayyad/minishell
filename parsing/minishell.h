#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>



typedef enum s_tokens
{
    WORD,
	D_QUOTED,
	S_QUOTED,
    PIPE,
	OR,
	AND,
	INPUT,
	OUTPUT,
	OUTPUT_APPEND,
	HERE_DOC,
	WHITE_SPACE,
	DOLLAR,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
}	t_tokens;

/*list for commands and redirection*/
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;
/*the syntax tree*/
typedef struct s_tree
{
	char			*str;
	int				type;
	t_list			*commands;
	t_list			*redirection;
	struct s_tree	*left;
	struct s_tree	*right;

}	t_tree;
/* Define the lexer struct */
typedef struct 		s_lexer
{
    char			*value;
    int				type;
    struct s_lexer	*next;
    struct s_lexer	*prev;
}					t_lexer;

/*lexical analysis*/
t_lexer	*new_token_ps(char *str, t_tokens token);
t_lexer	*lexer(char *input);

/*syntax*/
bool	syntax_checker_ps(t_lexer *tokens);
bool	double_checker_ps(char *input);
t_lexer	*remove_node_ps(t_lexer *head, int space);

int	ft_isalpha_ps(int x);
int	ft_isdigit_ps(int x);
/*new test*/
t_tree	*build_tree_ps(t_lexer *nodes);
t_tree	*and_or_case_ps(t_lexer **nodes);
t_tree *pipe_case_ps(t_lexer **nodes);

t_tree *cmd_node_ps(t_lexer **nodes);
t_tree *operator_node_ps(t_lexer **nodes);


t_list	*newnode_ps(char *data, t_tokens type);
t_tree	*new_tree_node_ps(t_lexer *nodes);
void	new_list_node_ps(t_list **new, char *content);

int	ft_lstsize_ps(t_list *lst);
t_list	*ft_lstlast_ps(t_list *lst);
t_list	*ft_lstnew_ps(char *content);
void	ft_lstadd_back_ps(t_list **lst, t_list *new);

t_lexer	*ft_lstnew_double(char *content);
void	ft_lstadd_back_double(t_lexer **lst, t_lexer *new);
/* execution */
void	execution(t_tree *node);
void	post_order(t_tree *root);


// t_tree	*build_tree_ps(t_lexer *nodes);
// t_tree	*and_or_case_ps(t_lexer **nodes);
// t_tree	*pipe_case_ps(t_lexer **nodes);
// t_tree *operator_node_ps(t_lexer **nodes);
// t_tree	*cmd_node_ps(t_lexer **nodes);
// t_tree	*switch_root(t_tree *new_root, t_tree *old_root);
// t_tree	*newnode_ps(char *data, t_tokens type);
// t_token		*create_token(int type, char  *value);
// t_lexer		*create_lexer(char *content);
// void		next_command_lexer(t_lexer *lexer);
// void		skip_whitespace(t_lexer *lexer);
// t_token		*get_next_token(t_lexer *lexer);
// t_token		*collect_string(t_lexer *lexer);//to parse strings between "" ex: "hello world hh"
// t_token		*collect_words(t_lexer *lexer);
// char		*get_current_char_as_string(t_lexer *lexer);

#endif