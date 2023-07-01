/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:45:43 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 02:01:48 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execve_error(char *cmd)
{
	if (cmd)
	{
		ft_printf("minishell: %s: command not found\n", cmd);
		exit(127);
	}
	exit(0);
}

void	access_error(char *cmd, char *str)
{
	if (access(cmd, F_OK) == -1)
		return (ft_printf("minishell: %s: No such file or directory\n", str),
			exit(127));
	if (access(cmd, X_OK) == -1)
		return (ft_printf("minishell: %s: Permission denied\n", str),
			exit(126));
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
