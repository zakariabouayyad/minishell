/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 06:03:16 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/24 12:46:24 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	stars_only_case(char *input)
{
	if (!input || input[0] == '\0')
		return (false);
	while (*input && *input == '*')
		input++;
	if (*input == '\0')
		return (true);
	return (false);
}

char	*get_first_file_name(t_list *lst)
{
	char	*s;

	while (lst && lst->content[0] == '.')
		lst = lst->next;
	if (!lst)
		return (NULL);
	s = lst->content;
	lst = lst->next;
	while (lst)
	{
		if (ft_strcmp(lst->content, s) < 0)
			s = lst->content;
		lst = lst->next;
	}
	return (s);
}

bool	if_stars_only(t_list **tokens, char *input, int *stars_cond)
{
	char	*first_fn;
	t_list	*tmp;
	t_list	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	*stars_cond = 0;
	if (!stars_only_case(input))
		return (false);
	tmp = get_folder_list(0);
	first_fn = get_first_file_name(tmp);
	ft_lstadd_back_double(&tmp2, ft_lstnew_double(first_fn));
	ft_lstadd_back_double(&tmp2, ft_lstnew_double(" "));
	ft_lstadd_back_double(&tmp2, ft_lstnew_double("*"));
	free_tlist(tmp);
	*tokens = tmp2;
	*stars_cond = 1;
	return (true);
}

bool	syntax_check_and_lexer(t_list **tokens, char *input)
{
	if (double_checker_ps(input) == false)
	{
		g_status = 258;
		free(input);
		printf("minishell: syntax error\n");
		return (false);
	}
	*tokens = lexer(input);
	*tokens = remove_node_ps(*tokens, WHITE_SPACE);
	if (syntax_checker_ps(*tokens) == false)
	{
		g_status = 258;
		free_list(*tokens);
		printf("minishell: syntax error\n");
		return (false);
	}
	return (true);
}

void printLinkedList(t_list *list)
{
    while (list)
    {
        printf("%s|", list->content);
        list = list->next;
    }
    printf("\n");
}

int print_tree(t_tree *tree)
{
    if (tree != NULL)
    {
		print_tree(tree->left);
        printLinkedList(tree->redirection);
        printLinkedList(tree->commands);
		print_tree(tree->right);
		return (1);
    }
	return (0);
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

void print_list_output(t_list *node)
{
	while (node)
	{
		printf("----------token(%d,%s)\n", node->type, node->content);
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

void	ft_minishell(t_envp **env_lst)
{
	t_list	*tokens;
	t_tree	*tree;
	char	*input;
	int		stars_cond;

	while (true)
	{
		input = show_prompt(*env_lst);
		if (input == NULL)
			handle_control_d(env_lst);
		if (if_stars_only(&tokens, input, &stars_cond) == false)
			if (syntax_check_and_lexer(&tokens, input) == false)
				continue ;
		print_list_output(tokens);
		tree = build_tree_ps(tokens);
		if (wild_card(&tree, *env_lst, stars_cond) == 0)
		{
			free_list(tokens);
			execute_tree(tree, env_lst, NULL,
				(t_flag){.in = 0, .out = 1, .pip = false, .wait_bool = true});
		}
		free_tree(tree);
		if (input != NULL)
			(free (input), input = (char *) NULL);
	}
}
