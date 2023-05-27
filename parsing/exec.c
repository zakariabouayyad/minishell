#include "minishell.h"

void	execution(t_tree *node)
{
	if (strcmp(node->commands->content, "|") == 0)
	{
		int	fd[2];
		int	pid;
		pipe(fd);
		pid = fork();
		if (!pid)
		{
			dup2(fd[0], 0);
			
		}
	}
}

void	post_order(t_tree *root)
{
	if (!root)
		return ;
	post_order(root->left);
	post_order(root->right);
	execution(root);
}