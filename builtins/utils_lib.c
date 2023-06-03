#include "../minishell.h"

t_envp	*ft_lstlast_envp(t_envp *lst)
{
	t_envp	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd_back_envp(t_envp **lst, t_envp *new)
{
	t_envp	*last;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last = ft_lstlast_envp(*lst);
			last->next = new;
		}
	}
}

int	ft_lstsize_envp(t_envp *lst)
{
	int	i;

	i = 0;
	while (lst && i++ >= 0)
		lst = lst->next;
	return (i);
}

t_envp	*ft_lstnew_envp(char *_variable, char *_value, int _shlvl_var)
{
	t_envp	*node;

	node = NULL;
	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	node->variable = _variable;
	node->value = _value;
	node->shlvl_var = _shlvl_var;
	node->includes_in_expt = 0;
	node->env_order = 0;
	node->end_exp = 0;
	node->chose = -1;
	node->next = 0;
	return (node);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*one;
	unsigned char	*two;

	i = 0;
	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	while (one[i] != '\0' && two[i] != '\0')
	{
		if ((one[i] == '\0' && two[i] != '\0') || (one[i] - two[i] < 0))
			return (one[i] - two[i]);
		else if ((one[i] != '\0' && two[i] == '\0') || (one[i] - two[i] > 0))
			return (one[i] - two[i]);
		i++;
	}
	if (one[i] != '\0' || two[i] != '\0')
		return (one[i] - two[i]);
	return (0);
}

char	*substr(char *s, unsigned int start, int end_char)
{
	unsigned int	i;
	char			*ret;

	if (!s)
		return (NULL);
	i = start;
	while (s[start] != '\0' && s[start] != end_char)
		start++;
	if (s[start] == '\0')
		return (NULL);
	ret = (char *)malloc((start - i) * sizeof(char));
	if (!ret)
		return (NULL);
	start = i;
	i = 0;
	while (s[start] != end_char)
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}