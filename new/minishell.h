#ifndef MINISHELL_H
#define MINISHELL_H

#include "minishell_ps.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/select.h>
# include <sys/wait.h>
#include <sys/file.h>
#include <sys/stat.h>

#include <locale.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#include <readline/readline.h>
#include <readline/history.h>

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

/*              utils               */
size_t	ft_strlen(const char *__s);
size_t	ft_strlen_var(const char *__s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	ft_free(char *s1, char *s2, char **array1, char **array2);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_atoi(const char *s);
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/*              lst.functions               */
t_envp	*ft_lstlast(t_envp *lst);
t_envp	*ft_lstnew(char *_variable, char *_value, int _shlvl_var);
void	ft_lstadd_back(t_envp **lst, t_envp *new);
int		ft_lstsize(t_envp *lst);


/*              built.in.commands               */
void	built_in_commands(t_envp **env_lst, t_lexer *tokens);

/*              export.command               */
void	execute_exprot(t_envp **env_lst, t_lexer *tokens);
char	*substr(char *s, unsigned int start, int end_char);
void	sort_lst(t_envp **expt_lst);
void	indexing(t_envp **lst);

/*              export.split               */
// export USER="khalid "zeganilol "lol2 c " plpsfl "   d""""""" "..."....
char	**export_split(const char *line_read);

/*              unset.command               */
void	execute_unset(t_envp **env_lst, t_lexer *tokens, int *list_size);

void	print_export(t_envp *expt_lst);
int		searsh_variable_name(char *var, char *searsh, unsigned int position);
void	add_variable(t_envp **expt_lst, char *var, char *val);
int		searsh_valiable(char *var, char *searsh, int len);
int		invalid_identifier_check(char *full_var, char *s);
char	*give_clean_value(const char *val);
t_envp	*locate_node(t_envp *lst);
void    export_with_value(t_envp **env_lst, char *var, char *val, int exist);
void	export_no_value(t_envp **env_lst, char *var, char *val, int exist);
void	export_no_eqaul_sign(t_envp **env_lst, char *var, char *val, int exist);
void	export_with_plus_equal_signs(t_envp **env_lst, char *var, char *val, int exist);
void	getting_lr_var_name(char *line_read , t_exp *e);
void	getting_lr_var_value(char *line_read , t_exp *e);
void	check_var_existens_in_export_list(t_envp *lst, char *line_read, t_exp *e);
void	fix_var_content(t_exp *e);
void	print_export(t_envp *expt_lst);
void	add_to_export(char *line_read, t_envp **expt_lst, int type, t_exp *e);
void	add_to_env(t_envp **expt_lst, int type, t_exp *e);

char	*joining_input(t_lexer **tokens);

// ➜ minishell$ export _=
// minishell(12933,0x10987edc0) malloc: *** error for object 0x104c98f58: pointer being freed was not allocated
// minishell(12933,0x10987edc0) malloc: *** set a breakpoint in malloc_error_break to debug

// [1]    12933 abort      ./minishell
#endif