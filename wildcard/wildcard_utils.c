/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 07:54:53 by kzegani           #+#    #+#             */
/*   Updated: 2023/06/24 08:54:28 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_fnmatch(const char *pattern, const char *string)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			if (*(pattern + 1) == '\0')
				return (true);
			while (*string)
			{
				if (ft_fnmatch(pattern + 1, string))
					return (true);
				string++;
			}
			return (false);
		}
		else if (*pattern == '?' || *pattern == *string)
		{
			pattern++;
			string++;
		}
		else
			return (false);
	}
	return (*string == '\0');
}

void	*print_error_dirent(char *to_print)
{
	perror(to_print);
	return (NULL);
}

t_list	*make_the_folder_list(DIR *dir, struct dirent *dp, int i)
{
	t_list	*lst;

	lst = NULL;
	while (dp != NULL)
	{
		i = errno;
		ft_lstadd_back(&lst, ft_lstnew(dp->d_name));
		dp = readdir(dir);
		if (dp == NULL && i != errno)
			return (ft_lstclear(&lst, free), print_error_dirent("Cannot read ."));
	}
	if (closedir(dir) != 0)
		return (ft_lstclear(&lst, free), print_error_dirent("Cannot close ."));
	return (lst);
}
