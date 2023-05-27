NAME = minishell

HEADER = minishell.h

CFLAGS = -g -lreadline

CC = cc

RM = rm -f

SRC = minishell.c lexer.c syntax_checker.c Ast/ast_build.c Ast/ast_utils.c Ast/node_handle.c exec.c #ast.c

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