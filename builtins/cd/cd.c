/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 05:01:48 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/24 02:27:16 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handl_oldpwd(t_envp *env_lst, t_envp *tmp1, t_envp *tmp2)
{
	char	*tmp;
	int		error;	

	tmp = get_content_of_node(env_lst, "OLDPWD");
	if (tmp == NULL)
		return (6);
	if (tmp)
		free(tmp);
	error = free_and_change(tmp2->value, tmp1->value, tmp1, tmp2);
	if (error == 0)
	{
		tmp = getcwd(NULL, PATH_MAX);
		printf("%s\n", tmp);
		free(tmp);
	}
	return (error);
}

static int	ft_chdir(t_envp **env_lst, char *home_path, char *new_path,
	char *_home_path)
{
	t_envp		*tmp1;
	t_envp		*tmp2;
	char		*tmp;

	tmp1 = *env_lst;
	tmp2 = *env_lst;
	while (ft_strcmp(tmp1->variable, "PWD") != 0)
		tmp1 = tmp1->next;
	while (ft_strcmp(tmp2->variable, "OLDPWD") != 0)
		tmp2 = tmp2->next;
	if (new_path == NULL && home_path == NULL)
		return (5);
	else if (new_path == NULL && home_path)
		return (free_and_change(home_path, tmp1->value, tmp1, tmp2));
	else if (new_path[0] == '\0')
		return (free_and_change(_home_path, tmp1->value, tmp1, tmp2));
	else if (ft_strcmp(new_path, "OLDPWD") == 0)
		return (handl_oldpwd(*env_lst, tmp1, tmp2));
	else
		return (free_and_change(new_path, tmp1->value, tmp1, tmp2));
	return (EXIT_SUCCESS);
}

static void	initializing_oldpwd(t_envp **env_lst, int *i)
{
	char	*str;

	*i = 1;
	str = get_content_of_node(*env_lst, "OLDPWD");
	if (str == NULL)
	{
		ft_lstadd_back_envp(env_lst,
			ft_lstnew_envp("OLDPWD", get_content_of_node(*env_lst, "PWD"), 0));
		indexing(env_lst);
		sort_lst(env_lst);
	}
	if (str)
		free(str);
}

int	hanl_cd_error(char *content, int error)
{
	char	*str;

	str = NULL;
	if (error == 5)
		printf("minishell: cd: HOME not set\n");
	else if (error == 6)
		printf("minishell: cd: OLDPWD not set\n");
	else
	{
		str = ft_strjoin("minishell: cd: ", content);
		perror(str);
		free(str);
	}
	return (EXIT_FAILURE);
}

int	change_directory(t_list *tokens, t_envp **env_lst, char *_home_path)
{
	int			error;
	char		*home_path;
	static int	i;

	if (!tokens || !env_lst || !(*env_lst))
		return (EXIT_FAILURE);
	if (i == 0)
		initializing_oldpwd(env_lst, &i);
	if (tokens->next)
		tokens = tokens->next->next;
	home_path = get_content_of_node(*env_lst, "HOME");
	if ((tokens->next == NULL && ft_strcmp(tokens->content, "cd") == 0))
		error = ft_chdir(env_lst, home_path, NULL, NULL);
	else if (ft_strcmp(tokens->content, "~") == 0)
		error = ft_chdir(env_lst, home_path, "", _home_path);
	else if (ft_strcmp(tokens->content, "-") == 0)
		error = ft_chdir(env_lst, home_path, "OLDPWD", NULL);
	else
		error = ft_chdir(env_lst, home_path, tokens->content, NULL);
	if (error != 0)
		return (hanl_cd_error(tokens->content, error));
	if (home_path)
		free(home_path);
	return (0);
}
