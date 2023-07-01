NAME = minishell

HEADER = minishell.h

CFLAGS = -g # -lreadline

READLINE = $(shell brew --prefix readline)

CC = cc

RM = rm -f

LIBSRC = $(addprefix libft/, ft_isdigit.o ft_lstiter.o ft_memcpy.o ft_split.o ft_strlen.o ft_tolower.o\
		ft_atoi.o ft_isprint.o ft_lstlast.o ft_memmove.o ft_strchr.o ft_strmapi.o ft_toupper.o\
		ft_bzero.o ft_itoa.o ft_lstmap.o ft_memset.o ft_strdup.o ft_strncmp.o\
		ft_calloc.o ft_lstadd_back.o ft_lstnew.o ft_putchar_fd.o ft_striteri.o ft_strnstr.o\
		ft_isalnum.o ft_lstadd_front.o ft_lstsize.o ft_putendl_fd.o ft_strjoin.o ft_strrchr.o\
		ft_isalpha.o ft_lstclear.o ft_memchr.o ft_putnbr_fd.o ft_strlcat.o ft_strtrim.o\
		ft_isascii.o ft_lstdelone.o ft_memcmp.o ft_putstr_fd.o ft_strlcpy.o ft_substr.o)

BUILTINS =	builtins/export/main_export.o builtins/export/ft_setenv.o builtins/export/ft_setenv_utils.o builtins/export/export_input_identifier.o	\
			builtins/exit/exit.o builtins/echo/echo.o builtins/cd/cd.o builtins/cd/cd_utils.o builtins/env/env.o builtins/unset/unset.o builtins/pwd/pwd.o	\
			expander/expander.o expander/multi_expands.o expander/extra_file.o	\
			builtins/utils_lib.o builtins/utils.o	\

EXECUTION =	execution/exec.o execution/more_exec.o execution/exec_errors.o execution/exec_utils.o execution/redirection.o	\
			other_utils.o free_functions.o main_minishell_utils.o make_env_list/env_lst.o	\
			wildcard/wildcard.o	wildcard/wildcard_utils.o \

FT_PRINTF = $(addprefix ft_printf/, ft_printf.o ft_putchar_pf.o ft_puthex_uper_pf.o ft_putstr_pf.o\
		ft_putadd_pf.o ft_puthex_pf.o ft_putnbr_pf.o ft_putunsigned_pf.o)

LEXER = $(addprefix lexer/, lexer.o syntax_checker.o handle_strings.o\
		redir_n_oper.o lexer_utils.o one_char.o more_syntax.o)

PARSING = $(addprefix parsing/, ast.o more_ast.o tree_utils.o more_tree_utils.o)

OBJ =	$(BUILTINS)\
		$(EXECUTION)\
		$(LEXER)\
		$(PARSING)\
		$(FT_PRINTF)\
		minishell.o\
		$(LIBSRC)\

# OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -L $(READLINE)/lib -lreadline $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I $(READLINE)/include -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re