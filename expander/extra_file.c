/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 05:22:23 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/24 10:31:05 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fix_lst(t_list **lst)
{
	t_list	*head;
	t_list	*list;
	int		i;

	head = *lst;
	while (head)
	{
		i = 0;
		if (head->type == D_QUOTED)
		{
			i = 1;
			list = head->next;
			fix_multi_sollar_in_d_quots(&head);
			head = list;
		}
		if (i != 1)
			head = head->next;
	}
}

void	extra_function(t_envp *env_lst, t_list **lst, t_list *head)
{
	char	*tmp;

	tmp = ft_expand(env_lst, head);
	printf("%s\n", head->content);
	free(head->content);
	printf("%s\n", head->content);
	if (tmp && head->prev == NULL)
	{
		expander_special_case(lst, &head, tmp);
		return ;
	}
	// free(head->content);
	if (tmp == NULL)
		head->content = ft_strdup("");
	else
		head->content = tmp;
}
