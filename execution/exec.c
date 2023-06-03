/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:44:05 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/03 21:15:42 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_exec(char *str, char *envp[])
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

t_fd	*ft_lstlast_fd(t_fd *lst)
{
	if (lst == NULL)
	{
		return (NULL);
	}
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_fd	*ft_lstnew_fd(int fd[2])
{
	t_fd	*new;

	new = (t_fd *)malloc(sizeof(t_fd));
	if (new == NULL)
		return (NULL);
	new->fd0 = fd[0];
	new->fd1 = fd[1];
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_fd(t_fd **lst, t_fd *new)
{
	t_fd	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		temp = ft_lstlast_fd(*lst);
		temp->next = new;
	}
}

// int	ft_lstsize_envp(t_envp *lst)
// {
// 	int	i;

// 	i = 0;
// 	while (lst && i++ >= 0)
// 		lst = lst->next;
// 	return (i);
// }

int	built_in_commands(t_envp **env_lst, t_list *tokens)
{
	static int	list_size;

	if (!tokens)
		return (-1);
	if (list_size == 0)
		list_size = ft_lstsize_envp(*env_lst);
	if (ft_strncmp(tokens->content, "exit", 5) == 0)
		ft_exit(tokens);
	else if (ft_strncmp(tokens->content, "echo", 5) == 0)
		echo(tokens);
	else if (ft_strncmp(tokens->content, "cd", 3) == 0)
		ft_cd(tokens);
	else if (ft_strncmp(tokens->content, "pwd", 4) == 0)
		current_working_directory();
	else if (ft_strncmp(tokens->content, "export", 7) == 0)
		execute_exprot(env_lst, tokens);
	else if (ft_strncmp(tokens->content, "env", 4) == 0)
		print_envp(env_lst, list_size);
	else if (ft_strncmp(tokens->content, "unset", 6) == 0)
		execute_unset(env_lst, tokens, &list_size);
	// else
	// 	other_commands(line_read, array, env_lst);
	return (-1);
}

int	is_built_in_commands(t_list *tokens)
{
	int	l;

	if (!tokens)
		return (0);
	l = ft_strlen(tokens->content);
	if (l == ft_strlen("exit") && ft_strncmp(tokens->content, "exit", l) == 0)
		return (1);
	else if (l == ft_strlen("echo") && ft_strncmp(tokens->content, "echo", l) == 0)
		return (1);
	else if (l == ft_strlen("cd") && ft_strncmp(tokens->content, "cd", l) == 0)
		return (1);
	else if (l == ft_strlen("pwd") && ft_strncmp(tokens->content, "pwd", l) == 0)
		return (1);
	else if (l == ft_strlen("export") && ft_strncmp(tokens->content, "export", l) == 0)
		return (1);
	else if (l == ft_strlen("env") && ft_strncmp(tokens->content, "env", l) == 0)
		return (1);
	else if (l == ft_strlen("unset") && ft_strncmp(tokens->content, "unset", l) == 0)
		return (1);
	return (0);
}

// void	read_in_tmp(char *lim, char *buf, int tmp)
// {
// 	int	l;

// 	l = ft_strlen(lim);
// 	while (buf && l == ft_strlen(buf) && ft_strncmp(lim, buf, ft_strlen(buf)) != 0)
// 	{
// 		puts(buf);
// 		write(tmp, buf, ft_strlen(buf));
// 		write(tmp, "\n", 1);
// 		free(buf);
// 		buf = readline("> ");
// 		// if (!buf)
// 		// 	unlink(".heredoc");
// 	}
// 	puts(buf);
// }

void	heredoc(char *lim)
{
	int		tmp;
	char	*buf;

	tmp = open(".heredoc", O_CREAT | O_RDWR , 0600);
	buf = readline("> ");
	puts(buf);
	
	int	l;

	l = ft_strlen(lim);
	while (buf && l == ft_strlen(buf) && ft_strncmp(lim, buf, ft_strlen(buf)) != 0)
	{
		puts(buf);
		write(tmp, buf, ft_strlen(buf));
		write(tmp, "\n", 1);
		free(buf);
		buf = readline("> ");
		// if (!buf)
		// 	unlink(".heredoc");
	}
	close(tmp);
	tmp = open(".heredoc", O_RDWR);
	dup2(tmp, STDIN_FILENO);
	close(tmp);
	unlink(".heredoc");
}

int rederection_case(t_tree *node, int in, int out)
{
	int	outfile;
	int	infile;
	int	l;

	if (node->redirection)
	{
		l = ft_strlen(node->redirection->content);
		if (l == 1 && ft_strncmp(node->redirection->content, ">", 1) == 0)
		{
			outfile = open(ft_lstlast(node->redirection)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);	
			dup2(outfile, out);
		}
		else if (l == 2 && ft_strncmp(node->redirection->content, ">>", 2) == 0)
		{
			outfile = open(ft_lstlast(node->redirection)->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(outfile, out);
		}
		else if (l == 1 && ft_strncmp(node->redirection->content, "<", 1) == 0)
		{
			infile = open(ft_lstlast(node->redirection)->content, O_RDONLY);
			dup2(infile, in);
		}
		else if (l == 2 && ft_strncmp(node->redirection->content, "<<", 2) == 0)
		{
			heredoc(ft_lstlast(node->redirection)->content);
		}
	}
	return (0);
}

int	execute_command(t_tree *node, char **envp, int in, int out, t_fd *fd_list, t_envp **env_lst, bool pip)
{
	pid_t	pid;
	int		status = 0;
	char	*cmd = NULL;

	if (pip == false && is_built_in_commands(node->commands))
	{
		rederection_case(node, in, out);
		status = built_in_commands(env_lst, node->commands);
		close(0);
		close(1);
		open(ttyname(STDERR_FILENO), O_RDONLY);
		open(ttyname(STDERR_FILENO), O_WRONLY);
	}
	else if (pip == true || !is_built_in_commands(node->commands))
	{
		pid = fork();
		if (!pid)
		{
			dup2(in, STDIN_FILENO);
			dup2(out, STDOUT_FILENO);
			while (fd_list)
			{
				close(fd_list->fd0);
				close(fd_list->fd1);
				fd_list = fd_list->next;
			}
			rederection_case(node, in, out);
			if (is_built_in_commands(node->commands))
				status = built_in_commands(env_lst, node->commands);
			else
			{
				cmd = list_to_string(node->commands);
				ft_exec(cmd, envp);
			}
		}
	}
	// close(in);
	// close(out);
	// waitpid(pid, &status, 0);
	// while (wait(NULL) != -1)
	// 	;
	return (status);
}

int	execute_tree(t_tree *node, char **envp, int in, int out, t_envp **env_lst, bool pip, t_fd *fd_list)
{
	int	res;

	if (!node)
		return (0);
	else if (node->type == OR || node->type == AND)
	{
		res = execute_tree(node->left, envp, in, out, env_lst, false , fd_list);
		if ((node->type == OR && res != 0)
			|| (node->type == AND && res == 0))
			res = execute_tree(node->right, envp, in, out, env_lst, false , fd_list);
	}
	else if (node->type == PIPE)
	{
		int	fd[2];

		pipe(fd);
		ft_lstadd_back_fd(&fd_list, ft_lstnew_fd(fd));
		execute_tree(node->left, envp, in, fd[1], env_lst, true , fd_list);
		close(fd[1]);
		res = execute_tree(node->right, envp, fd[0], out, env_lst, true , fd_list);
		close(fd[0]);
	}
	else
	{
		res = execute_command(node, envp, in, out, fd_list, env_lst, pip);
	}
	return (res);
}
