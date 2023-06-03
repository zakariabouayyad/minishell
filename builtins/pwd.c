#include "../minishell.h"

// void	ft_pwd(void)
// {
// 	char	pwd[PATH_MAX];
// 	char	*res;

// 	res = ft_strdup(getcwd(pwd, sizeof(pwd)));
// 	if (!res)
// 		perror("getcwd() error");
// 	else
// 		printf("%s\n", res);
// 	free (res);
// 	return ;
// }

/* change the allocation part */

void	current_working_directory(void)
{
	char	*cwd;

	cwd = (char *)malloc(300 * sizeof(char));
	getcwd(cwd, 300);
	if (cwd == NULL)
		printf("%s\n", strerror(errno));
	else
		printf("%s\n", cwd);
	free(cwd);
	return ;
}
