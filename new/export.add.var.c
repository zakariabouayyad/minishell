#include "minishell.h"

void	getting_lr_var_name(char *line_read , t_exp *e)
{
	// initializing all variables
	e->var = NULL;
	e->val = NULL;
	e->count = 0;
	e->cond = 0;

	e->count = ft_strlen_var(line_read);
	e->var = (char *)malloc(e->count * sizeof(char) + 1);
	e->var = ft_substr(line_read, 0, e->count);
}

void	getting_lr_var_value(char *line_read , t_exp *e)
{
	int	size;

	e->str = ft_strchr(line_read, '=');
	if (e->str != NULL && (e->str[1] != '\0' || (e->str[0] == '=' && e->str[1] == '\0')))
	{
		size = ft_strlen(e->str + 1);
		if (size > 0)
		{
			e->val = (char *)malloc(size * sizeof(char) + 1);
			ft_strlcpy(e->val, e->str + 1, size);
		}
		else
		{
			e->val = (char *)malloc(1 * sizeof(char));
			e->val[0] = 0;
		}
	}
	else
		e->val = NULL;
}

void	check_var_existens_in_export_list(t_envp *lst, char *line_read, t_exp *e)
{
	while (lst != NULL)
	{
		lst->located = 0;
		if (searsh_valiable(lst->variable, line_read, e->count) == TRUE)
		{
			e->cond = 1;
			lst->located = 1;
			return ;
		}
		lst = lst->next;
	}
}

void	fix_var_content(t_exp *e)
{
	int	i;

	i = 0;
	while (e->var[i])
	{
		if (e->var[i] == '+' && e->var[i + 1] == '\0')
		{
			e->var[i] = '\0';
			break ;
		}
		i++;
	}
}

void	add_to_export(char *line_read, t_envp **expt_lst, int type, t_exp *e)
{
	// t_envp	*tmp;

	// tmp = *expt_lst;
	(void)line_read;
	(void)expt_lst;
	(void)type;
	(void)e;
	// // getting the name of the variable
	// getting_lr_var_name(line_read , e);
	// if (e->var[0] == '_' && e->var[1] == '\0')
	// 	return ;
	// // getting the value of the variable
	// getting_lr_var_value(line_read , e);

	// // checking if the given variable exists in export list
	// check_var_existens_in_export_list(tmp, line_read, e);

	// // fixing the var content in this condition ==> lol+="some content"
	// fix_var_content(e);

	// printf("var ==> %s\n", e->var);
	// // filling the export list
	// if (type == EXP_W_VAL)
	// 	export_with_value(expt_lst, e, TRUE);
	// else if (type == EXP_N_VAL)
	// 	export_with_value(expt_lst, e, TRUE);
	// else if (type == EXP_N_EQU)
	// 	export_no_eqaul_sign(expt_lst, e);
	// else if (type == EXP_W_P_EQU)
	// 	export_with_plus_equal_signs(expt_lst, e, TRUE);
}
