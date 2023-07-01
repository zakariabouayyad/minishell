/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:14:06 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 08:28:08 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	if_fork_exit(t_envp **env_lst, t_list *commands, bool fork)
{
	if (fork == false)
		return ;
	free_lst(env_lst);
	free_tlist(commands);
	if (g_status == 0)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

void	built_in_commands(t_envp **env_lst, t_list *commands, bool fork)
{
	static char	*_home_path;
	static int	list_size;

	if (!commands)
		return ;
	if (list_size == 0)
	{
		_home_path = get_content_of_node(*env_lst, "HOME");
		list_size = ft_lstsize_envp(*env_lst);
	}
	if (ft_strncmp(commands->content, "exit", 5) == 0)
		ft_exit(commands, env_lst);
	else if (ft_strncmp(commands->content, "echo", 5) == 0)
		echo(commands);
	else if (ft_strncmp(commands->content, "cd", 3) == 0)
		g_status = change_directory(commands, env_lst, _home_path);
	else if (ft_strncmp(commands->content, "pwd", 4) == 0)
		current_working_directory(*env_lst);
	else if (ft_strncmp(commands->content, "export", 7) == 0)
		execute_exprot(env_lst, commands);
	else if (ft_strncmp(commands->content, "env", 4) == 0)
		g_status = print_envp(env_lst, list_size);
	else if (ft_strncmp(commands->content, "unset", 6) == 0)
		execute_unset(env_lst, commands, &list_size);
	if_fork_exit(env_lst, commands, fork);
}

int	is_built_in_commands(t_list *cmd)
{
	int	l;

	if (!cmd)
		return (0);
	l = ft_strlen(cmd->content);
	if (l == ft_strlen("exit") && ft_strncmp(cmd->content, "exit", l) == 0)
		return (1);
	else if (l == ft_strlen("echo") && ft_strncmp(cmd->content, "echo", l) == 0)
		return (1);
	else if (l == ft_strlen("cd") && ft_strncmp(cmd->content, "cd", l) == 0)
		return (1);
	else if (l == ft_strlen("pwd") && ft_strncmp(cmd->content, "pwd", l) == 0)
		return (1);
	else if (l == ft_strlen("export")
		&& ft_strncmp(cmd->content, "export", l) == 0)
		return (1);
	else if (l == ft_strlen("env") && ft_strncmp(cmd->content, "env", l) == 0)
		return (1);
	else if (l == ft_strlen("unset")
		&& ft_strncmp(cmd->content, "unset", l) == 0)
		return (1);
	return (0);
}
