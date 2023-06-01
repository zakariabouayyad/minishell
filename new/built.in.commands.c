#include "minishell.h"

void	echo(t_lexer *tokens)
{
	tokens = tokens->next;
	while (tokens != NULL)
	{
		printf("%s ", tokens->value);
		tokens = tokens->next;
	}
	printf ("\n");
	return ;
}

void	change_directory(t_lexer *tokens)
{
	if (chdir(tokens->next->value) != 0)
		perror("Error");
	return ;
}

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

void	print_envp(t_envp **env_lst, int list_size)
{
	t_envp		*tmp;
	int			loc;
	int			size;

	if (!env_lst)
		return ;
	loc = 1;
	size = ft_lstsize(*env_lst);
	while (loc <= list_size)
	{
		tmp = *env_lst;
		while (tmp && loc != tmp->env_order)
			tmp = tmp->next;
		if (tmp && tmp->includes_in_expt != 1)
		{
			if (tmp->shlvl_var != 0)
				printf("%s=%d\n", tmp->variable, tmp->shlvl_var);
			else if (tmp->value == NULL || tmp->value[0] == '\0')
				printf("%s=\n", tmp->variable);
			else
				printf("%s=%s\n", tmp->variable, tmp->value);
		}
		loc++;
	}
	tmp = *env_lst;
	while (tmp && loc-- > 1)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->includes_in_expt != 1)
		{
			if (tmp->shlvl_var != 0)
				printf("%s=%d\n", tmp->variable, tmp->shlvl_var);
			else if (tmp->value == NULL)
				printf("%s=\n", tmp->variable);
			else
				printf("%s=%s\n", tmp->variable, tmp->value);
		}
		tmp = tmp->next;
	}
}

void	other_commands(const char *line_read, char **array, t_envp **env_lst)
{
	(void)env_lst;
	if (ft_strncmp(line_read, "./minishell", 12) == 0)
		puts("./minishell level up\n");
	else
		printf("minishell: %s: command not found\n", array[0]);
}

void	execute_exit(char *num)
{
	int	status;

	status = ft_atoi(num);
	if (status == 256)
		(printf("exit\n"), exit(0));
	else if (status > 256)
	{
		while (status > 256)
			status -= 256;
		(printf("exit\n"), exit(status));
	}
	else
		(printf("exit\n"), exit(status));
}

void	ft_exit_alpha_error(t_lexer *tokens)
{
	t_lexer	*tmp;
	int		i;
	int		j;

	i = 1;
	tmp = tokens->next;
	while (tokens != NULL)
	{
		j = 0;
		while (tokens->value[j] != '\0' && ft_isdigit(tokens->value[j]) == 1)
			j++;
		if (tokens->value[j] == '\0' && ++i)
			tokens = tokens->next;
		else if (++i)
		{
			tokens = tokens->next;
			break ;
		}
	}
	if (i == 1)
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n", tokens->value);
		exit(NAR);
	}
	else if ((tokens->value != NULL || ft_isdigit(tokens->prev->value[j]) == 0) && i != 2)
		printf("exit\nminishell: exit: too many arguments\n");
	else
		execute_exit(tmp->value);
}

void	ft_exit(t_lexer *tokens)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	if (i == 1)
		(printf("exit\n"), exit(0));
	else if (i >= 2)
		ft_exit_alpha_error(tokens);
}

void	built_in_commands(t_envp **env_lst, t_lexer *tokens)
{
	static int	list_size;

	if (!tokens)
		return ;
	if (list_size == 0)
		list_size = ft_lstsize(*env_lst);
	if (ft_strncmp(tokens->value, "exit", 5) == 0)
		ft_exit(tokens);
	else if (ft_strncmp(tokens->value, "echo", 5) == 0)
		echo(tokens);
	else if (ft_strncmp(tokens->value, "cd", 3) == 0)
		change_directory(tokens);
	else if (ft_strncmp(tokens->value, "pwd", 4) == 0)
		current_working_directory();
	else if (ft_strncmp(tokens->value, "export", 7) == 0)
		execute_exprot(env_lst, tokens);
	else if (ft_strncmp(tokens->value, "env", 4) == 0)
		print_envp(env_lst, list_size);
	else if (ft_strncmp(tokens->value, "unset", 6) == 0)
		execute_unset(env_lst, tokens, &list_size);
	// else
	// 	other_commands(line_read, array, env_lst);
	return ;
}
