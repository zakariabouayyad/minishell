#include "minishell.h"

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

void	indexing_env_order(t_envp **lst)
{
	t_envp	*tmp;
	int		i;

	if (!lst)
		return ;
	i = 1;
	tmp = *lst;
	while (tmp)
	{
		tmp->env_order = i;
		tmp = tmp->next;
		i++;
	}
}

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
	count = ft_lstsize(*env_lst);
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

void	make_env_list(char *envp[], t_envp **env_lst)
{
	char			*tmp;
	char			*tmp2;
	char			*tmp3;
	unsigned int	size;
	unsigned int	i;
	unsigned int	shlvl;

	i = 0;
	shlvl = 0;
	while (envp[i] != NULL)
	{
		tmp = substr(envp[i], 0, '=');
		tmp2 = getenv(tmp);
		size = ft_strlen(tmp2);
		tmp3 = (char *)malloc(size * sizeof(char) + 1);
		ft_strlcpy(tmp3, tmp2, size);
		if (shlvl == 0 && ft_strnstr(envp[i], "SHLVL=", 6) != NULL)
		{
			shlvl = ft_atoi(&envp[i][6]) + 1;
			ft_lstadd_back(env_lst, ft_lstnew(tmp, tmp3, shlvl));
		}
		else
			ft_lstadd_back(env_lst, ft_lstnew(tmp, tmp3, 0));
		i++;
	}
	indexing_env_order(env_lst);
	indexing(env_lst);
	sort_lst(env_lst);
	indexing(env_lst);
}

int main(int ac, char *av[], char *envp[])
{
	const char		*prompt;
	static char		*line_read;
	t_lexer			*tokens = NULL;
	t_tree			*tree = NULL;
	t_envp			*temp = NULL;
	t_envp			*env_lst = NULL;

	(void)ac;
	(void)av;
	make_env_list(envp, &env_lst);
	temp = ft_lstlast(env_lst);
	temp->end_exp = 1;
	prompt = "minishell-1.0$ ";
	line_read = (char *)NULL;
	while (TRUE)
	{
		if (line_read)
			(free (line_read), line_read = (char *)NULL);
		line_read = readline(prompt);
		if (line_read != NULL && line_read[0] != '\0')
		{
			add_history(line_read);
			tokens = lexer(line_read);
			tokens = remove_node_ps(tokens, WHITE_SPACE);
			tree = build_tree_ps(tokens);
			// print_lexer_output(tokens);
			tree = for_export(tree);
			built_in_commands(&env_lst, tokens);
		}
	}
}