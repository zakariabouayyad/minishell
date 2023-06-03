#include "../minishell.h"

// void	newl_or_not(t_list *cur, bool new_line)
// {
// 	while (cur)
// 	{
// 		printf("%s", cur->content);
// 		cur = cur->next;
// 	}
// 	if (new_line)
// 		printf("\n");
// }

// void	ft_echo(t_list *head)
// {
// 	t_list	*cur;
// 	bool	new_line;

// 	if (!head)
// 		return ;
// 	cur = head;
// 	new_line = true;
// 	if (strcmp(cur->content, "echo") == 0)
// 	{
// 		if (cur->next)
// 		{
// 			cur = cur->next;
// 			while (strcmp(cur->content, " ") == 0)
// 				cur = cur->next;
// 			if (strcmp(cur->content, "-n") == 0)
// 			{
// 				new_line = false;
// 				cur = cur->next;
// 			}
// 		}
// 	}
// 	while (strcmp(cur->content, " ") == 0)
// 		cur = cur->next;
// 	newl_or_not(cur, new_line);
// }


/*khalid 's*/

void	echo(t_list *tokens)
{
	tokens = tokens->next;
	while (tokens != NULL)
	{
		printf("%s ", tokens->content);
		tokens = tokens->next;
	}
	printf ("\n");
	return ;
}