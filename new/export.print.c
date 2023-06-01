#include "minishell.h"

void	print_export(t_envp *env_lst)
{
	while (env_lst != NULL)
	{
		if (env_lst->shlvl_var != 0)
		{
			printf("declare -x %s=\"%d\"\n", env_lst->variable,
				env_lst->shlvl_var);
		}
		else if (env_lst->value == NULL)
			printf("declare -x %s\n", env_lst->variable);
		else
		{
			printf("declare -x %s=\"%s\"\n", env_lst->variable,
				env_lst->value);
		}
		env_lst = env_lst->next;
	}
}