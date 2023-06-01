#include "minishell.h"

char	*var_clean_content(char *full_var)
{
	int		i;
	char	*ret;

	if (!full_var || full_var[0] == '\0')
		return (NULL);
	if (ft_strchr(full_var, '=') != NULL)
	{
		ret = (char *)malloc((((ft_strchr(full_var, '=')
			- full_var) + 1)) * sizeof(char));
	}
	else
		ret = (char *)malloc((ft_strlen(full_var)) * sizeof(char));
	i = 0;
	while (*full_var)
	{
		ret[i++] = *full_var;
		if (*full_var == '=')
			break ;
		full_var++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*val_clean_content(char *full_val)
{
	char	*ret;
	int		size;

	if (!full_val || full_val[1] == '\0')
		return (NULL);
	full_val++;
	printf("strchr_var --> %s|\n", full_val);
	size = ft_strlen(full_val);
	ret = (char *)malloc((size + 1) * sizeof(char));
	if (size)
		ft_strlcpy(ret, full_val, size + 1);
	else
		ret[0] = '\0';
	return (ret);
}

int		invalid_identifier_check(char *full_var, char *s)
{
	if (!full_var || (!ft_isalpha(*full_var) && *full_var != '_'))
		return (FALSE);
	while (*full_var && *full_var != '=' && *full_var != '+')
	{
		if (!ft_isalnum(*full_var) && *full_var != '_')
			return (FALSE);
		full_var++;
	}
	if (full_var[0] == '+' && full_var[1] == '=' && full_var[2] == '\0')
		return (EXP_W_P_EQU);
	if (full_var[0] == '\0')
		return (EXP_N_EQU);
	full_var = ft_strchr(s, '=');
	if (full_var && full_var[1] == '\0')
		return (EXP_N_VAL);
	else if (full_var)
		return (EXP_W_VAL);
	return (FALSE);
}

int		searsh_valiable(char *var, char *searsh, int len)
{
	int	i;

	i = 0;
	while (i < len && var[i] == searsh[i])
		i++;
	if (i != len)
		return (FALSE);
	else if (searsh[i] == '\0' && var[i] == '\0')
		return (TRUE);
	return (FALSE);
}

int		var_existens_in_env_lst(t_envp *env_lst, char *var)
{
	int		size;

	size = ft_strlen(var);
	while (env_lst != NULL)
	{
		env_lst->located = 0;
		if (searsh_valiable(env_lst->variable, var, size) == TRUE)
		{
			env_lst->located = 1;
			return (TRUE);
		}
		env_lst = env_lst->next;
	}
	return (FALSE);
}

void	ft_setenv(char *var, char *val, t_envp **env_lst, int type)
{
	t_exp	e;

	e.i = -1;
	// fixing the var content in this condition ==> lol+="some content"
	while (var[++e.i])
		if (var[e.i] == '+' || var[e.i] == '=')
			var[e.i++] = '\0';
	// printf("||||||||||||=> %s\n", var);
	// printf("||||||||||||=> %s\n", val);

	// checking if the given variable exists in export list
	e.num = var_existens_in_env_lst(*env_lst, var);

	if (type == EXP_W_VAL)
		export_with_value(env_lst, var, val, e.num);
	else if (type == EXP_N_VAL)
		export_no_value(env_lst, var, val, e.num);
	else if (type == EXP_N_EQU)
	{
		puts("hello");
		export_no_eqaul_sign(env_lst, var, val, e.num);
	}
	else if (type == EXP_W_P_EQU)
		export_with_plus_equal_signs(env_lst, var, val, e.num);
}

char	*joining_input(t_lexer **tokens)
{
	char	*tmp;
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	while (i == FALSE && *tokens != NULL && ft_strcmp((*tokens)->value, " ") != 0)
	{
		if ((*tokens)->value[0] == '\0'
			&& (*tokens)->prev->value[ft_strlen((*tokens)->prev->value) - 1] == '=')
			i = TRUE;
		else
		{
			tmp = str;
			str = ft_strjoin(tmp, (*tokens)->value);
			if (tmp)
				free(tmp);
		}
		*tokens = (*tokens)->next;
	}
	return (str);
}

void	execute_exprot(t_envp **env_lst, t_lexer *tokens)
{
	t_exp	e;

	e.i = 0;
	e.str = NULL;
	tokens = tokens->next;
	if (tokens == NULL)
		print_export(*env_lst);
	else
	{
		tokens = tokens->next;
		while (tokens != NULL)
		{
			// joining the input to be correct
			e.str = joining_input(&tokens);

			// getting the correct content of var and val
			e.var = var_clean_content(e.str);
			e.val = val_clean_content(ft_strchr(e.str, '='));

			// printf("e.var1 --> %s|\n", e.var);
			// printf("e.val1 --> %s|\n", e.val);

			// in case of lol="" I need to make val equal to ""
			if (tokens && e.val == NULL && tokens->value[0] == '\0')
				e.val = ft_strdup("");

			// check for invalid identifier
			e.type = invalid_identifier_check(e.var, e.str);

			// print error or re initialize type var
			if (e.type == FALSE)
				printf("minishell: export: `%s': not a valid identifier\n", e.var);
			else if (e.type == EXP_N_VAL && e.i == TRUE)
				e.type = EXP_W_VAL;

			// input is correct
			if (e.var && !(e.var[0] == '_' && e.var[1] == '\0'))
				ft_setenv(e.var, e.val, env_lst, e.type);
			
			// freing the variables
			(free(e.str), e.str = NULL);
			(ft_free(e.var, e.val, NULL, NULL), e.i = FALSE);
			if (tokens == NULL)
				return ;
			tokens = tokens->next;
		}
	}
}
