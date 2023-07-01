/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_input_identifier.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:55:07 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/23 23:42:04 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*joining_input(t_list **lst)
{
	char	*tmp;
	char	*str;
	int		i;

	if (!lst || !*lst || !(*lst)->content)
		return (NULL);
	i = 0;
	str = NULL;
	while (i == FALSE && *lst != NULL && ft_strcmp((*lst)->content, " ") != 0)
	{
		if ((*lst)->content[0] == '\0'
			&& (*lst)->prev->content[ft_strlen((*lst)->prev->content) - 1]
			== '=')
			i = TRUE;
		else
		{
			tmp = str;
			str = ft_strjoin(tmp, (*lst)->content);
			if (tmp)
				free(tmp);
		}
		*lst = (*lst)->next;
	}
	return (str);
}

char	*var_clean_content(char *full_var)
{
	char	*ret;
	int		i;

	if (!full_var)
		return (NULL);
	if (full_var[0] == '\0' || full_var[0] == '=')
		return (ft_strdup(full_var));
	ret = ft_strchr(full_var, '=');
	i = 0;
	if (ret)
		while (i < (ret - full_var))
			i++;
	if (ret && full_var[i - 1] == '+')
		ret = ft_substr(full_var, 0, ret - full_var - 1);
	else if (ret)
		ret = ft_substr(full_var, 0, ret - full_var);
	else
		ret = ft_strdup(full_var);
	return (ret);
}

char	*val_clean_content(char *full_val)
{
	char	*ret;
	int		size;

	if (!full_val)
		return (NULL);
	if (ft_strcmp(full_val, "=") == 0)
		return (ft_strdup(""));
	return (ft_strdup(full_val + 1));
}

int	invalid_identifier_check(char *full_var)
{
	if (!full_var || (!ft_isalpha(*full_var) && *full_var != '_'))
		return (FALSE);
	while (*full_var && *full_var != '=' && *full_var != '+')
	{
		if (!ft_isalnum(*full_var) && *full_var != '_')
			return (FALSE);
		full_var++;
	}
	if (full_var[0] == '+' && full_var[1] == '=')
		return (EXP_W_P_EQU);
	if (full_var[0] == '\0')
		return (EXP_N_EQU);
	if (full_var && full_var[1] == '\0')
		return (EXP_N_VAL);
	else if (full_var && full_var[0] != '+')
		return (EXP_W_VAL);
	return (FALSE);
}
