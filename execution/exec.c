#include "../minishell.h"

void	execution(t_tree *node)
{
	if (strcmp(node->commands->content, "echo") == 0)
		ft_echo(node->commands);
	else if (strcmp(node->commands->content, "pwd") == 0)
		ft_pwd();
	else if (strcmp(node->commands->content, "cd") == 0)
	{
		if (ft_cd(node->commands) < 0)
			printf("No such file or directory\n");
	}
	// else if (strcmp(node->commands->content, "|") == 0)
	// {
	// 	int	fd[2];
	// 	int	pid;
	// 	pipe(fd);
	// 	pid = fork();
	// 	if (!pid)
	// 	{
	// 		dup2(fd[0], 0);
			
	// 	}
	// }
}

void	post_order(t_tree *root)
{
	if (!root)
		return ;
	post_order(root->left);
	post_order(root->right);
	execution(root);
}