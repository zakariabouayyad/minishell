/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:06:35 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/24 08:27:23 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_lst(t_envp **lst)
{
	if (!lst || !(*lst))
		return ;
	while ((*lst))
	{
		free((*lst)->variable);
		free((*lst)->value);
		free((*lst));
		*lst = (*lst)->next;
	}
}

static void	print_and_exit(char *to_print, int exit_status, t_envp **env_lst)
{
	free_lst(env_lst);
	if (to_print == NULL)
		write(STDOUT_FILENO, "exit\n", 5);
	else
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			to_print);
	}
	exit(exit_status);
}

static void	execute_exit(char *num, t_envp **env_lst)
{
	int	status;

	status = ft_atoi(num);
	if (status == -1 || status == 0)
		if (ft_strlen(num) > 1)
			print_and_exit(num, 255, env_lst);
	while (status >= 256)
		status -= 256;
	print_and_exit(NULL, status, env_lst);
}

static void	ft_exit_alpha_error(t_list *cmds, t_envp **env_lst)
{
	t_utils	x;

	x.i = 0;
	while (cmds != NULL && ++x.i)
	{
		x.j = -1;
		if (x.i == 2)
		{
			printf("exit\nminishell: exit: too many arguments\n");
			g_status = 1;
			return ;
		}
		while (cmds->content[++x.j] != '\0')
		{
			if ((!ft_isdigit(cmds->content[x.j])
					|| (x.j == 0 && ft_strcmp(cmds->content, "-") == 0))
				&& !((cmds->content[x.j] == '-' || cmds->content[x.j] == '+')
					&& x.j == 0))
				print_and_exit(cmds->content, NAR, env_lst);
		}
		if (cmds->next == NULL)
			break ;
		cmds = cmds->next;
	}
	execute_exit(cmds->content, env_lst);
}

void	ft_exit(t_list *commands, t_envp **env_lst)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = commands;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	if (i == 1)
		print_and_exit(NULL, EXIT_SUCCESS, env_lst);
	else if (i >= 2)
		ft_exit_alpha_error(commands->next->next, env_lst);
}
