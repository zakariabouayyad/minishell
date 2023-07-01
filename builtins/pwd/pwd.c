/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:52:41 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/24 08:27:37 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// needs to be fixed
void	current_working_directory(t_envp *env_lst)
{
	char	*cwd;
	int		error;

	error = errno;
	while (env_lst && ft_strcmp(env_lst->variable, "PWD") != 0)
		env_lst = env_lst->next;
	if (env_lst)
		printf("%s\n", env_lst->value);
	g_status = (error != errno);
}
