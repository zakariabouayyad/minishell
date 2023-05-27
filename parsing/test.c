


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












t_tree	*newnode_ps(char *data, t_tokens type)
{
	t_tree	*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->content = ft_strdup(data);
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

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

t_tree	*cmd_node_ps(t_lexer *nodes)
{
	// if the type is D_QUOTED or S_QUOTED it takes the content who is a char * (string) and give it to the function
	//  lexer() which will parse the content in list if there is "| or || or &&" or rerirections "< << > >>"
	// then take the output of lexer() and go through each node and if its a redirection it get put in that node of the tree in a list just for redirections
	// and if its a normal command it get put in the same node of the tree in a list just for commades
	// now else if its not D_QUOTED and S_QUOTED we take the content of the node ant we put it in a tree node that has a list in the command list
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

t_tree	*pipe_case_ps(t_lexer *nodes)
{
	t_tree	*tree;
	t_tree *new_root = NULL;
    t_tree *old_root = NULL;

	tree = cmd_node_ps(nodes);
	while (nodes->type == PIPE)
	{
		new_root = switch_root(new_root, old_root);
		tree->right = cmd_node_ps(nodes);
	}
	return (tree);
}

t_tree	*and_or_case_ps(t_lexer *nodes)
{
	t_tree	*tree;
	t_tree *new_root = NULL;
    t_tree *old_root = NULL;

	old_root = pipe_case_ps(nodes);
	while (nodes->type == OR || nodes->type == AND)
	{
		new_root = switch_root(new_root, old_root);
		tree->right = pipe_case_ps(nodes);
	}
	return (tree);
}

t_tree	*build_tree_ps(t_lexer *nodes)
{
	return (and_or_case_ps(nodes));
}