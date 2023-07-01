/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 06:07:45 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/24 10:27:35 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*make_star_list(t_list *lst, t_list *wc_lst)
{
	t_utils	x;
	t_list	*tmp;
	t_list	*last;
	t_list	*head;

	x.i = 1;
	head = NULL;
	tmp = lst->next;
	while (wc_lst)
	{
		if (ft_fnmatch(lst->content, wc_lst->content))
			ft_lstadd_back(&head, ft_lstnew(wc_lst->content));
		wc_lst = wc_lst->next;
	}
	return (head);
}

void	fix_wild_card_in_node(t_list *lst, t_list *wc_lst)
{
	t_list	*tmp;
	t_list	*head;

	while (lst)
	{
		if (ft_strchr(lst->content, '*') != NULL)
		{
			head = make_star_list(lst, wc_lst);
			if (head == NULL)
			{
				lst = lst->next;
				continue ;
			}
			ft_lstjoin(lst, head);
		}
		else
			lst = lst->next;
	}
}

t_list	*get_folder_list(int star_cond)
{
	int				i;
	DIR				*dir;
	struct dirent	*dp;

	i = 0;
	dir = opendir (".");
	if (dir == NULL)
		return (print_error_dirent("Cannot open ."));
	i = errno;
	dp = readdir(dir);
	if (dp == NULL && i != errno)
		return (print_error_dirent("Cannot read ."));
	if (star_cond)
	{
		while (dp != NULL && dp->d_name[0] == '.')
		{
			i = errno;
			dp = readdir(dir);
			if (dp == NULL && i != errno)
				return (print_error_dirent("Cannot read ."));
		}
	}
	return (make_the_folder_list(dir, dp, i));
}

void	w_c_tree_loop(t_tree *tree, t_list *lst, t_envp *env_lst)
{
	if (!tree)
		return ;
	w_c_tree_loop(tree->left, lst, env_lst);
	fix_wild_card_in_node(tree->commands, lst);
	expander(&tree->commands, env_lst);
	w_c_tree_loop(tree->right, lst, env_lst);
}

int	wild_card(t_tree **tree, t_envp *env_lst, int star_cond)
{
	t_list	*lst;

	lst = get_folder_list(star_cond);
	w_c_tree_loop(*tree, lst, env_lst);
	free_tlist(lst);
	return (0);
}
