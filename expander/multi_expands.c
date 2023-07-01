/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_expands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:55:18 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 05:14:06 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_singl_quote(char *s, t_utils *x)
{
	int	i;

	x->i = 0;
	x->str1 = NULL;
	x->str2 = NULL;
	x->tmp1 = NULL;
	i = 0;
	while (s[i] == '\'')
		i++;
	return (i);
}

static char	*start_end_join(char *s, int count)
{
	char	*tmp;
	char	*ret;
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	i = -1;
	ret = NULL;
	tmp = (char *)malloc((count + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (++i < count)
		tmp[i] = '\'';
	tmp[i] = '\0';
	ret = ft_strjoin(tmp, s);
	str = ret;
	ret = ft_strjoin(ret, tmp);
	ft_free(s, str, NULL, NULL);
	return (ret);
}

char	*multi_expands(t_envp *env_lst, char *lst)
{
	t_utils	x;

	if (!env_lst || !lst)
		return (NULL);
	x.j = count_singl_quote(lst, &x);
	if (x.j != 0)
		lst = ft_strtrim(lst, "\'");
	x.temp = ft_split(lst, '$');
	while (x.temp[x.i])
	{
		x.tmp1 = get_content_of_node(env_lst, x.temp[x.i]);
		if (x.tmp1)
		{
			x.str1 = x.str2;
			x.str2 = ft_strjoin(x.str2, x.tmp1);
			ft_free(x.tmp1, x.str1, NULL, NULL);
		}
		x.i++;
	}
	if (x.j != 0)
		x.str2 = start_end_join(x.str2, x.j);
	ft_free(NULL, NULL, x.temp, NULL);
	return (x.str2);
}

void	fix_multi_sollar_in_d_quots(t_list **head)
{
	t_list	*lst;
	t_list	*tmp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while ((*head)->content && (*head)->content[i] && j < 2)
	{
		if ((*head)->content[i] == '$')
			j++;
		i++;
	}
	if (j < 2)
		return ;
	lst = lexer((*head)->content);
	tmp = (*head)->prev;
	free((*head)->content);
	free(*head);
	tmp->next = lst;
	lst->prev = tmp;
	tmp = ft_lstlast(lst);
}
