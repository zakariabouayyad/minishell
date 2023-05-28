#include "../minishell.h"

void	ft_pwd(void)
{
	char	pwd[PATH_MAX];
	char	*res;

	res = strdup(getcwd(pwd, sizeof(pwd)));
	if (!res)
		perror("getcwd() error");
	else
		printf("%s\n", res);
	free (res);
	return ;
}
