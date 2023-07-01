/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:52:34 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 10:35:45 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_content_of_node(t_envp *env_lst, char *search)
{
	if (!env_lst)
		return (NULL);
	while (env_lst && ft_strcmp(env_lst->variable, search) != 0)
		env_lst = env_lst->next;
	if (env_lst == NULL)
		return (NULL);
	return (ft_strdup(env_lst->value));
}

int	check_to_expand(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (FALSE);
	if (s[0] == ' ' && s[1] == '\0')
		return (FALSE);
	while (s[i])
	{
		if (s[i] == '$' && (s[i + 1] == '?' || (!ft_isdigit(s[i + 1])
					&& (ft_isalpha(s[i + 1]) || s[i + 1] == '_'))))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	expander_special_case(t_list **lst, t_list **head, char *tmp)
{
	t_list	*tokens;
	t_list	*node;

	*lst = (*lst)->next;
	free(*head);
	tokens = lexer(tmp);
	tokens = remove_node_ps(tokens, WHITE_SPACE);
	node = *lst;
	*lst = tokens;
	ft_lstlast(*lst)->next = node;
	*head = node;
}

char	*ft_expand(t_envp *env_lst, t_list *head)
{
	if (head->type == D_QUOTED)
		return (multi_expands(env_lst, head->content));
	else
		return (get_content_of_node(env_lst, head->content + 1));
	return (NULL);
}

void	expander(t_list **lst, t_envp *env_lst)
{
	t_list	*head;

	if (!lst || !env_lst)
		return ;
	fix_lst(lst);
	head = *lst;
	while (head)
	{
		if (head->type != S_QUOTED && check_to_expand(head->content) == TRUE)
		{
			if (ft_strcmp(head->content, "$?") == 0)
			{
				free(head->content);
				head->content = ft_itoa(g_status);
				head = head->next;
				continue ;
			}
			extra_function(env_lst, lst, head);
		}
		head = head->next;
	}
	while (*lst && ((*lst)->content == NULL || (*lst)->content[0] == ' '
			|| (*lst)->content[0] == '\0'))
		*lst = (*lst)->next;
}
