/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 04:50:59 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/24 08:26:53 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	start_printing(t_list *lst, int nl_opt)
{
	while (lst)
	{
		if (lst->content)
			write(STDOUT_FILENO, lst->content, ft_strlen(lst->content));
		lst = lst->next;
	}
	if (nl_opt == FALSE)
		write (STDOUT_FILENO, "\n", 1);
}

static int	new_line_option(char *content)
{
	int	i;
	int	nl_opt;

	i = 2;
	nl_opt = TRUE;
	while (content[i])
	{
		if (content[i] != 'n')
		{
			nl_opt = FALSE;
			break ;
		}
		i++;
	}
	return (nl_opt);
}

static int	ft_echo(t_list *lst, int nl_opt, int error)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (nl_opt == TRUE && lst->content[0] == '-' && lst->content[1] == 'n')
		{
			i = 2;
			while (lst->content[i] && lst->content[i] == 'n')
				i++;
		}
		if (lst->content[i] && ft_strcmp(lst->prev->content, " ") == 0
			|| ft_strcmp(lst->prev->content, "") == 0)
		{
			start_printing(lst, nl_opt);
			return (error != errno);
		}
		i = 0;
		lst = lst->next;
	}
	return (error != errno);
}

void	echo(t_list *lst)
{
	int	error;
	int	nl_opt;

	error = errno;
	nl_opt = FALSE;
	if (lst && ft_lstsize(lst) == 1 || (ft_lstsize(lst) == 3
			&& lst->next->next->content[0] == '\0'))
	{
		write(STDOUT_FILENO, "\n", 1);
		g_status = error != errno;
		return ;
	}
	lst = lst->next->next;
	if (lst && lst->content[0] == '-' && lst->content[1] == 'n')
		nl_opt = new_line_option(lst->content);
	ft_echo(lst, nl_opt, error);
	g_status = error != errno;
}
