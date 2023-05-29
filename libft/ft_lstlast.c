/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:02:58 by zbouayya          #+#    #+#             */
/*   Updated: 2023/05/29 20:15:06 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstlast(t_list *lst)
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
