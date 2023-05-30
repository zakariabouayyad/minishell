#include "../minishell.h"

static char	**ft_freeall(char **list, int i )
{
	while (list[i])
	{
		free(list[i]);
		i--;
	}
	free(list);
	return (NULL);
}

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	listsize;
	size_t	i;

	i = 0;
	listsize = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || \
		(s[i] == c && s[i + 1] != c && s[i + 1] != '\0'))
			listsize++;
		i++;
	}
	return (listsize);
}

char	**ft_split_gnl(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;
	size_t	save;

	i = 0;
	j = -1;
	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (ft_wordcount((char *)s, c) + 1));
	if (!str)
		return (NULL);
	while (++j < ft_wordcount((char *)s, c))
	{
		while (s[i] == c && s[i])
			i++;
		save = i;
		while (s[i] != c && s[i])
			i++;
		str[j] = ft_substr(s, save, i - save);
		if (!str)
			return (ft_freeall(str, j - 1));
	}
	str[j] = NULL;
	return (str);
}

void	add_cmd(char **paths, char **cmd)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		// protect_char(paths[i]);
		paths[i] = ft_strjoin(paths[i], cmd[0]);
		// protect_char(paths[i]);
		i++;
	}
}

void	if_path(char *paths[], char *envp[])
{
	if (access(paths[0], F_OK | X_OK) == 0)
	{
		execve(paths[0], paths, envp);
			// execve_error();
	}
	// else
	// 	access_error(paths[0]);
}

void	path(char *str, char *envp[])
{
	char	**paths;
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split_gnl(str, ' ');
	// protect_d_char(cmd);
	if (ft_strnstr(cmd[0], "/", ft_strlen(str)) != NULL)
		if_path(cmd, envp);
	else
	{
		while (ft_strncmp(envp[i], "PATH=", 5))
			i++;
		paths = ft_split_gnl(envp[i], ':');
		// protect_d_char(paths);
		add_cmd(paths, cmd);
		i = -1;
		while (paths[++i])
			if (access(paths[i], F_OK | X_OK) == 0)
				break ;
		// access_error(paths[i]);
		execve(paths[i], cmd, envp);
			// execve_error();
	}
}


void handle_pipe_operator(t_tree *left_command, t_tree *right_command, char **envp)
{
    int pipefd[2];

    pipe(pipefd);

    // Execute the left command
    pid_t left_pid = fork();
    if (left_pid == 0)
	{
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

       path(left_command->commands->content, envp);
    }

    // Execute the right command
    pid_t right_pid = fork();
    if (right_pid == 0)
	{
        close(pipefd[1]); 
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

       path(right_command->commands->content, envp);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for the right command to finish executing
    int status;
    // waitpid(right_pid, &status, 0);
}



void	execution(t_tree *node, char **envp)
{
	// if (strcmp(node->commands->content, "exit") == 0)
	// {
	// 	printf("exit\n");
	// 	exit(EXIT_SUCCESS);
	// }
	// if (strcmp(node->commands->content, "echo") == 0)
	// 	ft_echo(node->commands);
	// else if (strcmp(node->commands->content, "pwd") == 0)
	// 	ft_pwd();
	// else if (strcmp(node->commands->content, "cd") == 0)
	// {
	// 	if (ft_cd(node->commands) < 0)
	// 		printf("No such file or directory\n");
	// }
	// else if (strcmp(node->commands->content, "|") == 0)
	// {
	// 	handle_pipe_operator(node->left ,node->right, envp);
	// }
}

int	execute_command(t_tree *left_node, t_tree *right_node)
{

}
int	execute_pipe(t_tree *left_node, t_tree *right_node)
{
}
int	execute_syntax_tree(t_tree *node, char **envp)
{
	if (!node)
		return ;
	if (node->type == PIPE)
	{
		return(execute_pipe(execute_syntax_tree(node->left, envp), execute_syntax_tree(node->right, envp)));
	}
	else if (node->type == OR)
	{
		if (execute_syntax_tree(node->left, envp) == 0)/*is successful*/
			return (execute_syntax_tree(node->left, envp));
		else
			execute_syntax_tree(node->right, envp);
	}
	else if (node->type == AND)
	{
		if (execute_syntax_tree(node->left, envp) == 0)/*is successful*/
			return (execute_syntax_tree(node->right, envp));
		else
			execute_syntax_tree(node->left, envp);
	}
	else
	{
		execute_command(node->left, node->right);
	}
	return (0);
}