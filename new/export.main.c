#include "minishell.h"

void	execute_exprot(const char *line_read, t_envp **env_lst, t_envp **expt_lst)
{
	t_exp	e;

	(void)env_lst;
	e.i = 0;
	e.tmp = NULL;
	e.str = ft_strchr(line_read, ' ');
	if (e.str)
	{
		while (*e.str == ' ')
			e.str++;
		e.tmp = export_split(e.str);
	}
	if (e.tmp == NULL)
		print_export(*expt_lst);
	else
	{
		while (e.tmp[e.i] != NULL)
		{
			if (invalid_identifier_check(e.tmp[e.i], &e.type) == FALSE)
			{
				add_to_export(e.tmp[e.i], expt_lst, e.type, &e);
				add_to_env(env_lst, e.type, &e);
			}
			else if (e.tmp[e.i][0] != '\0')
				printf("minishell: export: `%s': not a valid identifier\n", e.tmp[e.i]);
			e.i++;
		}
	}
}
