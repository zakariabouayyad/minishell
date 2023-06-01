#include "minishell.h"

void	remove_node(t_envp **lst, int id)
{
	t_envp	*tmp;
	t_envp	*prev;

	if (lst == NULL || *lst == NULL)
		return;
	prev = NULL;
	tmp = *lst;
	while (tmp != NULL && tmp->id != id)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return;
	if (prev == NULL)
		*lst = tmp->next;
	else
		prev->next = tmp->next;
	ft_free(tmp->variable, tmp->value, NULL, NULL);
	free(tmp);
	indexing(lst);
}

int		unset_invalid_identifier_check(char *s)
{
	int	i;

	i = 1;
	if (s[0] != '_' && (ft_isdigit(s[0]) || !ft_isalpha(s[0])))
		return (TRUE);
	while (s[i] != '\0' && (ft_isalnum(s[i]) || s[i] == ' ' || s[i] == '_' || s[i] == '-'))
		i++;
	if (!s[i])
		return (FALSE);
	return (TRUE);
}

void	unset_env_list(t_envp **env_lst, char *s)
{
	t_envp	*tmp;

	tmp = *env_lst;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->variable, s) == 0)
		{
			remove_node(env_lst, tmp->id);
			return ;
		}
		tmp = tmp->next;
	}
}

void	execute_unset(t_envp **env_lst, t_lexer *tokens, int *list_size)
{
	char	*str;

	str = NULL;
	tokens = tokens->next->next;
	while (tokens != NULL)
	{
		str = joining_input(&tokens);
		if (!(str[0] == '_' && str[1] == '\0'))
		{
			if (!unset_invalid_identifier_check(str))
				(unset_env_list(env_lst, str), list_size--);
			else
				printf("minishell: unset: `%s': not a valid identifier\n", str);
		}
		(free(str), str = NULL);
		if (tokens == NULL)
			return ;
		tokens = tokens->next;
	}
}