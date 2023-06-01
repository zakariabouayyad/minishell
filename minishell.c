#include "minishell.h"

// t_tree	*newnode_ps(int data)
// {
// 	t_tree	*new;
// 	new = malloc(sizeof(t_tree));
// 	if (new)
// 	{
// 		new->left = NULL;
// 		new->right = NULL;
// 		new->content = data;
// 	}
// 	return (new);
// }

// void	print_tree(t_tree *root)
// {
// 	if (root == NULL)
// 	{
// 		printf("mt\n");
// 		return ;
// 	}
// 	printf("content = %s\n", root->content);
// 	printf("left\n");
// 	print_tree(root->left);
// 	printf("right\n");
// 	print_tree(root->right);
// 	printf("done\n");
// }

// void print_tree(t_tree *root, int level) {
//     if (root == NULL) {
//         return;
//     }

//     // Print the current node
//     for (int i = 0; i < level; i++) {
//         printf("  "); // Indentation based on the level
//     }
// 	if (!root->commands)
// 		printf("%s\n", root->commands->content);
// 	if (root->redirection)
// 		printf("%s\n", root->redirection->content);

//     // Recursively print the left and right subtrees
//     print_tree(root->left, level + 1);
//     print_tree(root->right, level + 1);
// }

void printLinkedList(t_list *list)
{
    while (list)
    {
        printf("%s\n", list->content);
        list = list->next;
    }
}

void print_tree(t_tree *tree)
{
    if (tree != NULL)
    {
		print_tree(tree->left);
        printLinkedList(tree->redirection);
        printLinkedList(tree->commands);
		print_tree(tree->right);
    }
}

void printTree(t_tree *root, int level)
{
    int i;

    if (root == NULL)
        return;

    printTree(root->left, level + 1);

    for (i = 0; i < level; i++)
        printf("    ");

    printLinkedList(root->commands);
    printLinkedList(root->redirection);

    printTree(root->right, level + 1);
}

void	print_hh(t_tree *tree)
{
    if (tree != NULL)
    {
		// printf("%s\n", tree->content);
		// printf("%s\n", tree->commands->content);
		printf("%s\n", tree->left->commands->content);
		// printf("%s\n", tree->right->commands->content);
    }
}

char	*prompt(void)
{
	char *line;

	line = readline("\033[0;36mMinshell ➜ \033[0m");
	if (line == NULL)
		return (NULL);
	return (line);
}


// a function to print the lexer output
void print_lexer_output(t_lexer *node)
{
	while (node)
	{
		printf("----------token(%d,%s)\n", node->type, node->value);
		// if (node->prev == NULL)
        // 	printf("Previous node is NULL.\n");
		// else
		// 	printf("Previous token(%d, %s)\n", node->type, node->prev->value);
		// if (node->next == NULL)
        // 	printf("-----------------------next node is NULL.\n");
		// else
		// 	printf("-----------------------next token(%d, %s)\n", node->type, node->next->value);
		node = node->next;
	}
}

t_list *create_node(char *content)
{
    t_list *new_node = malloc(sizeof(t_list));
    if (new_node == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the new node.\n");
        return NULL;
    }
    new_node->content = strdup(content);
    new_node->next = NULL;
    return new_node;
}

void append_node(t_list **head, t_list *new_node)
{
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }
    t_list *current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
}

void print_list(t_list *head)
{
    t_list *current = head;
    while (current != NULL)
    {
        printf("%s ", current->content);
        current = current->next;
    }
    printf("\n");
}

char	*list_to_string(t_list* head)
{
	int len = 0;
	int i = 0;
	t_list* current = head;

	len = ft_lstsize_ps(current);
	char *str = (char*)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return NULL;
	current = head;
	while (current != NULL)
	{
		str = strcat(str, current->content);
		current = current->next;
	}	
	return (str);
}

// t_tree	*for_export(t_tree *tree)
// {
// 	if (tree == NULL)
// 		return (NULL);
// 	for_export(tree->left);
// 	if (strcmp(tree->commands->content, "export") == 0)
// 	{
// 		tree->str = list_to_string(tree->commands);
// 	}
// 	for_export(tree->right);
// 	return (tree);
// }

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
			ft_lstadd_back_envp(env_lst, ft_lstnew_envp(tmp, tmp3, shlvl));
		}
		else
			ft_lstadd_back_envp(env_lst, ft_lstnew_envp(tmp, tmp3, 0));
		i++;
	}
	indexing_env_order(env_lst);
	indexing(env_lst);
	sort_lst(env_lst);
	indexing(env_lst);
}

int main(int ac, char *av[], char *envp[])
{
	int		status;
	char	*input;
	t_lexer *tokens;
	t_tree	*tree;
	t_envp	*env_lst = NULL;
	
	(void)ac;
	(void)av;
	make_env_list(envp, &env_lst);
	while (1)
	{
		input = prompt();
		add_history(input);
		if (double_checker_ps(input) == false)
		{
			printf("syntax error\n");
			continue;
		}
		tokens = lexer(input);
		// remove_whitespace_from_list(tokens);
		tokens = remove_node_ps(tokens, WHITE_SPACE);
		if(syntax_checker_ps(tokens) == false)
		{
			free(tokens);
			printf("syntax error\n");
			continue;
		}
		// tokens = remove_quote(tokens);
		// tokens = concatenate_nodes(tokens);
		tree = build_tree_ps(tokens);
		t_fd *fd_list = malloc(sizeof(t_fd) * 100);
		status = execute_syntax_tree(tree, envp, 0, 1, fd_list, &env_lst);
		// print_hh(tree);
		// print_tree(tree);
		// printTree(tree, 0);
		// print_lexer_output(tokens);
		// system("leaks minishell");
	}

	free(input);
	return (status);
}