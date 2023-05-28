


	/**************************************************************
	****** what is the struct of the code should look like ********
	char	*line;
	t_token	*token_list;
	t_ast	*tree;

	while (1)
	{
		line = prompt();
		if (lexer(line, &token_list))
		{
			tree = to_tree(token_list);
			if (!tree)
				continue ;
		}
		else
			continue ;
		if (!execute_tree(tree))
			continue ;
	}
	*************************************************************/






t_tree	*switch_root(t_tree *new_root, t_tree *old_root)
{
	t_tree* original_root;

	if (!new_root || !old_root)
        return (NULL);
    // Store the original root of new_root
    original_root = new_root;
    // Set the root of new_root to the root of old_root
    new_root = old_root;
    // Attach the original new_root as the left child of the new root (old_root)
    new_root->left = original_root;

    return (new_root);
}

// t_tree	*operator_node_ps(t_lexer *nodes)
// {
// 	t_tree	*tree;

// 	while (nodes->type == PIPE || nodes->type == AND || nodes->type == OR)
// 	{
// 		// addvace to the next tokent to add
// 		tree = newnode_ps(nodes->value, nodes->type);
// 	}
// 	return (tree);
// }