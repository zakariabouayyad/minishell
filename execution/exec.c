/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:44:05 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 08:27:56 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_in_parent(t_tree *node, t_envp **env_lst, t_flag flags)
{
	rederection_case(node, flags.in, flags.out);
	if (!node->commands)
		return ;
	built_in_commands(env_lst, node->commands, false);
	close(0);
	close(1);
	open(ttyname(STDERR_FILENO), O_RDONLY);
	open(ttyname(STDERR_FILENO), O_WRONLY);
}

void	execute_in_child(t_tree *node, t_envp **env_lst, t_fd *fd_list,
	t_flag flags)
{
	char	**cmd;
	char	**envp;

	cmd = NULL;
	dup2(flags.in, STDIN_FILENO);
	dup2(flags.out, STDOUT_FILENO);
	while (fd_list)
	{
		close(fd_list->fd0);
		close(fd_list->fd1);
		fd_list = fd_list->next;
	}
	rederection_case(node, flags.in, flags.out);

	if (!node->commands)
	{
		ft_printf("minishell: : command not found\n");
		exit(0);
	}
	if (is_built_in_commands(node->commands))
		built_in_commands(env_lst, node->commands, true);
	else
	{
		envp = transfom_env_lst(*env_lst);
		cmd = list_to_string(node->commands);
		ft_exec(cmd, envp);
	}
}

void	execute_command(t_tree *node, t_envp **env_lst,
	t_fd *fd_list, t_flag flags)
{
	pid_t	pid;
	int		stat;

	stat = is_built_in_commands(node->commands);

	if (flags.pip == false && stat)
		execute_in_parent(node, env_lst, flags);
	else if (flags.pip == true || !stat)
	{
		pid = fork();
		if (!pid)
			execute_in_child(node, env_lst, fd_list, flags);
		if (flags.wait_bool)
		{
			waitpid(pid, &g_status, 0);
			g_status /= 256;
			while (wait(NULL) != -1)
				;
		}
	}
}

void	execute_pipe(t_tree *node, t_envp **env_lst,
	t_fd *fd_list, t_flag flags)
{
	int	fd[2];

	pipe(fd);
	ft_lstadd_back_fd(&fd_list, ft_lstnew_fd(fd));
	execute_tree(node->left, env_lst, fd_list, (t_flag){.in = flags.in,
		.out = fd[1], .pip = true, .wait_bool = false});
	close(fd[1]);
	execute_tree(node->right, env_lst, fd_list, (t_flag){.in = fd[0],
		.out = flags.out, .pip = true, .wait_bool = false});
	close(fd[0]);
	if (flags.wait_bool)
		while (wait(NULL) != -1)
			;
}

void	execute_tree(t_tree *node, t_envp **env_lst,
	t_fd *fd_list, t_flag flags)
{
	if (!node)
		return ;
	else if (node->type == OR || node->type == AND)
	{
		execute_tree(node->left, env_lst, fd_list, (t_flag){.in = flags.in,
			.out = flags.out, .pip = false, .wait_bool = true});
		if ((node->type == OR && g_status != 0)
			|| (node->type == AND && g_status == 0))
			execute_tree(node->right, env_lst, fd_list, (t_flag){.in = flags.in,
				.out = flags.out, .pip = false, .wait_bool = flags.wait_bool});
	}
	else if (node->type == PIPE)
		execute_pipe(node, env_lst, fd_list, flags);
	else
		execute_command(node, env_lst, fd_list, flags);
}
