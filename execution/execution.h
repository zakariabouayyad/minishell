#ifndef EXECUTION_H
#define EXECUTION_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../parsing/minishell.h"

void	execution(t_tree *node);
void	post_order(t_tree *root);

#endif