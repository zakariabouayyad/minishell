#include "../minishell.h"

char	*case_home(char *path)
{
	char	*new_path;

	if (path && path[0] == '~')
	{
		new_path = ft_strjoin(strdup(getenv("HOME")), strdup(&(path[1])));
		free(path);
		return (new_path);
	}
	return (path);
}

int	ft_cd(t_list *head)
{
	int	status;

	if (!head || !head->next)
		return(-1);
	status = 0;
	head = head->next;
	while (head->next && strcmp(head->content, " ") == 0)
		head = head->next;
	// status = directory_exists(head->content);
	// if (status < 0)
	// 	return (status);
	status = chdir(case_home(head->content));
	return (status);
}



/*needs to get fixed*/

// void	change_directory(t_list *tokens)
// {
// 	if (chdir(tokens->content) != 0)
// 		perror("Error");
// 	return ;
// }