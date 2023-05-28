NAME = minishell

HEADER = minishell.h

CFLAGS = -g -lreadline

CC = cc

RM = rm -f

SRC = minishell.c lexer/lexer.c lexer/syntax_checker.c parsing/ast.c parsing/more_ast.c parsing/tree_utils.c execution/exec.c builtins/echo.c builtins/pwd.c builtins/cd.c

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

PHONY : all clean fclean re