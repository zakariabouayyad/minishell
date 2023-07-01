/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 05:22:49 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/24 02:30:38 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	free_and_change(char *new_path, char *old_path, t_envp *tmp1,
	t_envp *tmp2)
{
	char	*tmp;

	if (chdir(new_path) != 0)
		return (1);
	free(tmp2->value);
	tmp2->value = ft_strdup(old_path);
	tmp = getcwd(NULL, PATH_MAX);
	if (tmp == NULL)
	{
		tmp = tmp1->value;
		printf("cd: error retrieving current directory: getcwd: ");
		printf("cannot access parent directories: No such file or directory\n");
		tmp1->value = ft_strjoin(tmp1->value, "/..");
		(free(tmp), tmp = NULL);
	}
	else
	{
		tmp1->value = ft_strdup(tmp);
		free(tmp);
	}
	return (0);
}
