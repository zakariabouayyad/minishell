/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:45:02 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 08:38:53 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <ctype.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <errno.h>
# include <signal.h>
# include <dirent.h>

# define NRMAL  "\x1B[0m"
# define RED  "\x1B[31m"
# define GREEN  "\x1B[32m"
# define YELLOW  "\x1B[33m"
# define BLUE  "\x1B[34m"
# define MAGENTA  "\x1B[35m"
# define CYAN  "\x1B[36m"
# define WHTITE  "\x1B[37m"

# define BRED  "\x1B[1;31m"
# define BGREEN  "\x1B[1;32m"
# define BYELLOW  "\x1B[1;33m"
# define BBLUE  "\x1B[1;34m"
# define BMAGENTA  "\x1B[1;35m"
# define BCYAN  "\x1B[1;36m"
# define BWHTITE  "\x1B[1;37m"

# define TMA 1
# define NAR 255
# define SUCCESS 0
# define CORRECT 0
# define ERROR 1

# define FALSE 0
# define TRUE 1

# define EXP_W_VAL 1 // variable=value
# define EXP_N_VAL 2 // variable=
# define EXP_N_EQU 3 // variable
# define EXP_W_P_EQU 4 // variable+=value

# define START 2
# define MIDL 3
# define END 4

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

/*struct envp*/
typedef struct envp
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
}				t_envp;

typedef struct s_swapnodes
{
	t_envp	*prevx;
	t_envp	*currx;
	t_envp	*prevy;
	t_envp	*curry;
	t_envp	*temp;
}					t_swapnodes;

/*list for commands and redirection*/
typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

/*fd list*/
typedef struct s_fd
{
	int			fd0;
	int			fd1;
	struct s_fd	*next;
}				t_fd;

int	g_status;

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

/*struct*/
typedef struct utils
{
	int		i;
	int		j;
	int		k;
	int		num;
	int		count;
	int		*nums;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	char	*str1;
	char	*str2;
	char	**temp;
	char	**ret;
}				t_utils;

typedef struct utils_expt_env
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

typedef struct s_flag
{
	int		in;
	int		out;
	bool	pip;
	bool	wait_bool;
}			t_flag;

void		ft_minishell(t_envp **env_lst);
char		*show_prompt(t_envp *env_lst);
void		handle_control_d(t_envp **env_lst);
bool		if_stars_only(t_list **tokens, char *input, int *stars_cond);
void		init(t_envp **env_lst, char **envp);
void		ft_lstjoin(t_list *lst, t_list *wc_lst);

/*       wildcard         */
void		*print_error_dirent(char *to_write);
bool		ft_fnmatch(const char *pattern, const char *string);
t_list		*make_the_folder_list(DIR *dir, struct dirent *dp, int i);
int			wild_card(t_tree **tree, t_envp *env_lst, int wow);

/*       some_free_functions         */
void		free_list(t_list *head);
void		free_tlist(t_list *head);
void		free_tree(t_tree *tree);

/*lexical analysis*/
t_list		*lexer(char *input);
int			tokenizer(t_list **head, t_list **tail, char *input, int i);
void		add_token(t_list **head, t_list **tail, char *token, t_tokens type);
t_list		*new_token_ps(char *str, t_tokens token);
int			handle_output(char *input, int i, t_list **head, t_list **tail);
int			handle_input(char *input, int i, t_list **head, t_list **tail);
int			hanele_pipe_n_or(char *input, int i, t_list **head, t_list **tail);
int			hanele_and(char *input, int i, t_list **head, t_list **tail);
int			handle_word(t_list **head, t_list **tail, int i, char *input);
int			handle_dollar(char *input, int i, t_list **head, t_list **tail);
int			handle_single_quoted(char *input, int i,
				t_list **head, t_list **tail);
int			handle_double_quoted(char *input, int i,
				t_list **head, t_list **tail);
int			handle_output(char *input, int i, t_list **head, t_list **tail);
int			handle_input(char *input, int i, t_list **head, t_list **tail);
int			hanele_pipe_n_or(char *input, int i, t_list **head, t_list **tail);
int			hanele_and(char *input, int i, t_list **head, t_list **tail);
int			handle_open_parenthesis(char *input, t_list **head, t_list **tail);
int			handle_close_parenthesis(char *input, t_list **head, t_list **tail);
int			handle_white_space(t_list **head, t_list **tail, char *str);
int			handle_status(char *input, int i, t_list **head, t_list **tail);
int			is_white_space(char c);
int			not_and(char c, char c1);
int			not_word(char c);
int			is_redirection(int tokens);
int			is_word(int token);
t_list		*remove_node_ps(t_list *head, int space);
bool		double_checker_ps(char *input);
bool		parentheses_closed(t_list *head);
bool		syntax_checker_ps(t_list *tokens);

int			ft_isalpha_ps(int x);
int			ft_isdigit_ps(int x);

/*      executing tree         */
int			rederection_case(t_tree *node, int in, int out);
void		ft_exec(char **str, char *envp[]);

/*      execution utils        */
void		execve_error(char *cmd);
void		access_error(char *cmd, char *str);
t_fd		*ft_lstlast_fd(t_fd *lst);
t_fd		*ft_lstnew_fd(int fd[2]);
void		ft_lstadd_back_fd(t_fd **lst, t_fd *new);

/*new test*/
t_tree		*build_tree_ps(t_list *nodes);
t_tree		*and_or_case_ps(t_list **nodes);
t_tree		*pipe_case_ps(t_list **nodes);

t_tree		*cmd_node_ps(t_list **nodes);
t_tree		*operator_node_ps(t_list **nodes);

void		ft_lstclear_double(t_list **lst);
t_list		*newnode_ps(char *data, t_tokens type);
t_tree		*new_tree_node_ps(t_list *nodes);
void		new_list_node_ps(t_list **new, char *content);

int			ft_lstsize_ps(t_list *lst);
t_list		*ft_lstlast_ps(t_list *lst);
t_list		*ft_lstnew_ps(char *content, int type);
void		ft_lstadd_back_ps(t_list **lst, t_list *new);

t_list		*ft_lstnew_double(char *content);
void		ft_lstadd_back_double(t_list **lst, t_list *new);

/* execution */
char		**list_to_string(t_list *head);
void		execute_tree(t_tree *node, t_envp **env_lst,
				t_fd *fd_list, t_flag flags);

/*         builtin commands        */
t_envp		*locate_node(t_envp *lst);
void		add_variable(t_envp **env_lst, char *var, char *val);
static int	searsh_valiable(char *var, char *searsh, int len);
int			var_existens_in_env_lst(t_envp *env_lst, char *var);
void		ft_setenv(char *var, char *val, t_envp **env_lst, int type);
char		*joining_input(t_list **lst);;
char		*var_clean_content(char *full_var);
char		*val_clean_content(char *full_val);
int			invalid_identifier_check(char *full_var);
void		execute_exprot(t_envp **env_lst, t_list *lst);
void		ft_exit(t_list *tokens, t_envp **env_lst);
int			free_and_change(char *new_path, char *old_path, t_envp *tmp1,
				t_envp *tmp2);
void		free_lst(t_envp **lst);
char		*multi_expands(t_envp *env_lst, char *lst);

/*             expander              */
void		fix_lst(t_list **lst);
void		extra_function(t_envp *env_lst, t_list **lst, t_list *head);
void		fix_multi_sollar_in_d_quots(t_list **head);
void		expander_special_case(t_list **lst, t_list **head, char *tmp);
char		*ft_expand(t_envp *env_lst, t_list *head);
void		expander(t_list **lst, t_envp *env_lst);

int			ft_cd(t_list *head);
int			ft_lstsize_envp(t_envp *lst);
void		echo(t_list *lst);
void		current_working_directory(t_envp *env_lst);
int			print_envp(t_envp **env_lst, int list_size);
void		execute_unset(t_envp **env_lst, t_list *tokens, int *list_size);
int			change_directory(t_list *tokens, t_envp **env_lst,
				char *_home_path);

/*utils */
void		indexing(t_envp **lst);
void		swapnodes(t_envp **head, int x, int y);
void		sort_lst(t_envp **env_lst);
void		ft_free(char *s1, char *s2, char **array1, char **array2);

/*libft env*/
t_envp		*ft_lstlast_envp(t_envp *lst);
void		ft_lstadd_back_envp(t_envp **lst, t_envp *new);
int			ft_lstsize_envp(t_envp *lst);
t_envp		*ft_lstnew_envp(char *_variable, char *_value, int _shlvl_var);
int			ft_strcmp(const char *s1, const char *s2);

/* libft */
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		**ft_split(char const *s, char c);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

char		*get_content_of_node(t_envp *env_lst, char *search);
int			ft_lstsize_envp(t_envp *lst);
int			check_to_expand(char *s);

void		printLinkedList(t_list *list);
char		**transfom_env_lst(t_envp *env_lst);
void		print_list(t_list *head);

void		add_cmd(char **paths, char **cmd);
int			is_built_in_commands(t_list *tokens);
void		built_in_commands(t_envp **env_lst, t_list *commands, bool fork);
char		**ft_split_gnl(char const *s, char c);
void		execve_error(char *cmd);
t_list		*get_folder_list(int star_cond);

/*  ft_printf   */
int			ft_printf(const char *str, ...);
int			ft_putstr_pf(char *str);
int			ft_putnbr_pf(int nb);
int			ft_putchar_pf(char c);
int			ft_puthex_upper_pf(unsigned int n);
int			ft_puthex_pf(unsigned int n);
int			ft_putunsigned_pf(unsigned int nb);
int			ft_putadd_pf(unsigned long long n);

/*        make_env_lst        */
void		make_env_list(char *envp[], t_envp **env_lst);

#endif
