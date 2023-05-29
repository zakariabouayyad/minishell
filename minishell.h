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
#include <sys/stat.h>



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
// void	execution(t_tree *node);
// void	post_order(t_tree *root);
void	post_order(t_tree *root, char **envp);

/*  builtins  */
void	ft_echo(t_list *head);
void	ft_pwd(void);
int	ft_cd(t_list *head);


/* libft */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char const *s, char c);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif