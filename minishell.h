#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
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

/*  builtins  */
void	ft_echo(t_list *head);
void	ft_pwd(void);
int	ft_cd(t_list *head);

#endif