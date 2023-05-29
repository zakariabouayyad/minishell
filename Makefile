NAME = minishell

HEADER = minishell.h

CFLAGS = -g -lreadline

CC = cc

RM = rm -f

LIBSRC = $(addprefix libft/, ft_isdigit.c ft_lstiter.c ft_memcpy.c ft_split.c ft_strlen.c ft_tolower.c\
		ft_atoi.c ft_isprint.c ft_lstlast.c ft_memmove.c ft_strchr.c ft_strmapi.c ft_toupper.c\
		ft_bzero.c ft_itoa.c ft_lstmap.c ft_memset.c ft_strdup.c ft_strncmp.c\
		ft_calloc.c ft_lstadd_back.c ft_lstnew.c ft_putchar_fd.c ft_striteri.c ft_strnstr.c\
		ft_isalnum.c ft_lstadd_front.c ft_lstsize.c ft_putendl_fd.c ft_strjoin.c ft_strrchr.c\
		ft_isalpha.c ft_lstclear.c ft_memchr.c ft_putnbr_fd.c ft_strlcat.c ft_strtrim.c\
		ft_isascii.c ft_lstdelone.c ft_memcmp.c ft_putstr_fd.c ft_strlcpy.c ft_substr.c)

SRC = minishell.c lexer/lexer.c lexer/syntax_checker.c parsing/ast.c parsing/more_ast.c parsing/tree_utils.c execution/exec.c builtins/echo.c builtins/pwd.c builtins/cd.c $(LIBSRC)

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re