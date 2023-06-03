/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:45:02 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/03 14:49:32 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include <errno.h>
#include <fcntl.h>


#define TMA 1
#define NAR 255
#define SUCCESS 0
#define CORRECT 0
#define ERROR 1

#define FALSE 0
#define TRUE 1

#define EXP_W_VAL 1 // variable=value
#define EXP_N_VAL 2 // variable=
#define EXP_N_EQU 3 // variable
#define EXP_W_P_EQU 4 // variable+=value

#define START 2
#define MIDL 3
#define END 4


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
	struct s_list	*prev;
}					t_list;

/*fd list*/
typedef struct s_fd
{
	int				fd0;
	int				fd1;
	struct s_fd	*next;
}					t_fd;
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


/*struct*/

typedef	struct  utils
{
	int			i;
	int			j;
	int			k;
	int			num;
	int			count;
	int			*nums;
	char		*tmp;
	char		**temp;
	char		**ret;
}				t_utils;

typedef	struct  utils_expt_env
{
	int			i;
	int			j;
	int			num;
	int			type;
	int			count;
	int			cond;
	char		*var;
	char		*val;
	char		*str;
	char		*tmp;
}				t_exp;

/*struct envp*/

typedef	struct  envp
{
	int			id;
	int			includes_in_expt;
	int			env_order;
	int			chose;
	int			located;
	char		*variable;
	char		*value;
	int			shlvl_var;
	int			end_exp;
	struct envp	*next;
}			  	t_envp;


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

int		ft_lstsize_ps(t_list *lst);
t_list	*ft_lstlast_ps(t_list *lst);
t_list	*ft_lstnew_ps(char *content);
void	ft_lstadd_back_ps(t_list **lst, t_list *new);

t_lexer	*ft_lstnew_double(char *content);
void	ft_lstadd_back_double(t_lexer **lst, t_lexer *new);
/* execution */
// void	execution(t_tree *node);
// void	post_order(t_tree *root);
char	*list_to_string(t_list* head);
// int	execute_tree(t_tree *node, char **envp, int in, int out, t_fd *fd_list);
int	execute_tree(t_tree *node, char **envp, int in, int out, t_envp **env_lst, bool pip, t_fd *fd_list);

/*  builtins  */
// void	ft_echo(t_list *head);
// void	ft_pwd(void);
int		ft_cd(t_list *head);

int		ft_lstsize_envp(t_envp *lst);
void	ft_exit_alpha_error(t_list *tokens);
void	ft_exit(t_list *tokens);
void	echo(t_list *tokens);
void	change_directory(t_list *tokens);
void	current_working_directory(void);
void	execute_exprot(t_envp **env_lst, t_list *tokens);
void	print_envp(t_envp **env_lst, int list_size);
void	execute_unset(t_envp **env_lst, t_list *tokens, int *list_size);

/*utils */
void	indexing(t_envp **lst);
void	swapNodes(t_envp** head, int x, int y);
void	sort_lst(t_envp **env_lst);
char	*joining_input(t_list **tokens);
void	ft_free(char *s1, char *s2, char **array1, char **array2);

/*libft env*/
t_envp	*ft_lstlast_envp(t_envp *lst);
void	ft_lstadd_back_envp(t_envp **lst, t_envp *new);
int	ft_lstsize_envp(t_envp *lst);
t_envp	*ft_lstnew_envp(char *_variable, char *_value, int _shlvl_var);
int	ft_strcmp(const char *s1, const char *s2);
char	*substr(char *s, unsigned int start, int end_char);

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