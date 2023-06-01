NAME= minishell
CFLAGS= -g -Wall -Wextra -Werror
HEADER= minishell.h
CC= cc
RM= rm -f

OBJ=	main.o built.in.commands.o utils.o ft_split.o					\
		lst.functions.o ft_atoi.o ft_isdigit.o ft_strchr.o				\
		ft_strnstr.o ft_isalnum.o ft_isalpha.o export.split.o			\
		unset.command.o env.add.var.o exp.env.utils.o exp.env.utils2.o	\
		export.add.var.o zzz.main.enviroment.fun.o export.print.o		\
		minishell.o lexer.o syntax_checker.o Ast/ast_build.o			\
		Ast/ast_utils.o Ast/node_handle.o								\

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME)

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) $< -o $@

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: clear intro re

.PHONY: clean clear fclean all re run