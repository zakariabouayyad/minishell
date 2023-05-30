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

t_tree	*for_export(t_tree *tree)
{
	if (tree == NULL)
		return (NULL);
	for_export(tree->left);
	if (strcmp(tree->commands->content, "export") == 0)
	{
		tree->str = list_to_string(tree->commands);
	}
	for_export(tree->right);
	return (tree);
}

int main(int ac, char *av[], char *envp[])
{
	char	*input;
	t_lexer *tokens;
	t_tree	*tree;
	
	ac = 1;
	av = NULL;
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
		tree = for_export(tree);
		execute_syntax_tree(tree, envp);
		// print_hh(tree);
		// print_tree(tree);
		// printTree(tree, 0);
		// print_lexer_output(tokens);
		// system("leaks minishell");
	}

	free(input);
}