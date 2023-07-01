/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:45:49 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 02:42:10 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_cmd(char **paths, char **cmd)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd[0]);
		i++;
	}
}

void	if_path(char *paths[], char *envp[])
{
	access_error(paths[0], *paths);
	if (access(paths[0], F_OK | X_OK) == 0)
	{
		if (execve(paths[0], paths, envp) < 0)
			execve_error(*paths);
	}
}

void	ft_exec(char **cmd, char *envp[])
{
	char	**paths;
	int		i;

	if (!envp)
		return (ft_printf("TERM environment variable not set.\n"), exit(127));
	i = 0;
	if (ft_strnstr(cmd[0], "/", ft_strlen(cmd[0])) != NULL)
		if_path(cmd, envp);
	else
	{
		while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
			i++;
		paths = ft_split(envp[i] + 5, ':');
		add_cmd(paths, cmd);
		i = -1;
		while (paths && paths[++i])
			if (access(paths[i], F_OK | X_OK) == 0)
				break ;
		if (!paths)
			return (ft_printf("minishell: %s: command not found\n", (*cmd)),
				exit(127));
		if (execve(paths[i], cmd, envp) < 0)
			execve_error(*cmd);
	}
}
