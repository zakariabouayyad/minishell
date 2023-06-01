#include "minishell.h"

// void	export_with_plus_equal_signs(t_envp **lst, t_exp *e, int sort)
// {
// 	t_envp	*tmp;

// 	tmp = locate_node(*lst);
// 	if (tmp == NULL)
// 		tmp = ft_lstlast(*lst);
// 	if (e->cond == 1)
// 		{
// 			if (!e->val)
// 				tmp->value = ft_strjoin(tmp->value, "");
// 			else
// 				tmp->value = ft_strjoin(tmp->value, give_clean_value(e->val));
// 		}
// 		else
// 			add_variable(lst, e->var, e->val, sort);
// }
