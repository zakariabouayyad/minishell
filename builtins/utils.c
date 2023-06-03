#include "../minishell.h"

void	indexing(t_envp **lst)
{
	t_envp	*tmp;
	int		i;

	if (!lst)
		return ;
	i = 1;
	tmp = *lst;
	while (tmp)
	{
		tmp->id = i;
		tmp = tmp->next;
		i++;
	}
}

void	swapNodes(t_envp** head, int x, int y) {
    // If x and y are the same, no swapping needed
    if (x == y) return;

    // Initialize pointers for the first and second t_envps
    t_envp* prevX = NULL;
    t_envp* currX = *head;
    t_envp* prevY = NULL;
    t_envp* currY = *head;

    // Search for nodes x and y and their previous nodes
    while (currX && currX->id != x) {
        prevX = currX;
        currX = currX->next;
    }
    while (currY && currY->id != y) {
        prevY = currY;
        currY = currY->next;
    }

    // If either x or y is not found, return
    if (!currX || !currY) return;

    // Adjust the next pointers to swap the nodes
    if (prevX) prevX->next = currY;
    else *head = currY;
    if (prevY) prevY->next = currX;
    else *head = currX;

    t_envp* temp = currX->next;
    currX->next = currY->next;
    currY->next = temp;
}
void	sort_lst(t_envp **env_lst)
{
	t_envp	*tmp;
	int		i;
	int		count;

	i = 0;
	count = ft_lstsize_envp(*env_lst);
	while (i < count - 1)
	{
		tmp = *env_lst;
		while (tmp && tmp->next != NULL)
		{
			if (ft_strcmp(tmp->variable, tmp->next->variable) > 0)
				swapNodes(env_lst, tmp->id, tmp->next->id);
			tmp = tmp->next;
		}
		i++;
	}
	indexing(env_lst);
}

char	*joining_input(t_list **tokens)
{
	char	*tmp;
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	while (i == FALSE && *tokens != NULL && ft_strcmp((*tokens)->content, " ") != 0)
	{
		if ((*tokens)->content[0] == '\0'
			&& (*tokens)->prev->content[ft_strlen((*tokens)->prev->content) - 1] == '=')
			i = TRUE;
		else
		{
			tmp = str;
			str = ft_strjoin(tmp, (*tokens)->content);
			if (tmp)
				free(tmp);
		}
		*tokens = (*tokens)->next;
	}
	return (str);
}

void	ft_free(char *s1, char *s2, char **array1, char **array2)
{
	int	i;

	i = 0;
	if (s1)
		(free(s1), s1 = NULL);
	if (s2)
		(free(s2), s2 = NULL);
	if (array1)
	{
		while (array1[i] != NULL)
			(free(array1[i]), array1[i++] = NULL);
		(free(array1), array1 = NULL);
	}
	if (array2)
	{
		while (array2[i] != NULL)
			(free(array2[i]), array2[i++] = NULL);
		(free(array2), array2 = NULL);
	}
	return ;
}