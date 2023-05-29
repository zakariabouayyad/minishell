#include "../minishell.h"


// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// char	*ft_substr(const char *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*sub;

// 	i = 0;
// 	j = 0;
// 	if (!s)
// 		return (NULL);
// 	if (len >= ft_strlen(s))
// 		len = ft_strlen(s);
// 	sub = (char *)malloc(sizeof(*s) * (len + 1));
// 	if (!sub)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		if (i >= start && j < len)
// 		{
// 			sub[j] = s[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	sub[j] = '\0';
// 	return (sub);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*s3;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1)
// 		return (ft_substr(s2, 0, ft_strlen(s2)));
// 	if (!s2)
// 		return (ft_substr(s1, 0, ft_strlen(s1)));
// 	s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (!s3)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		s3[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 		s3[i++] = s2[j++];
// 	s3[i] = '\0';
// 	free(s1);
// 	return (s3);
// }

// int	directory_exists(char *path)
// {
// 	int	status;

// 	if (stat(path, &status) < 0)
// 		return (status);
// 	return (status);
// }

char	*case_home(char *path)
{
	char	*new_path;

	if (path && path[0] == '~')
	{
		new_path = ft_strjoin(strdup(getenv("HOME")), strdup(&(path[1])));
		free(path);
		return (new_path);
	}
	return (path);
}

int	ft_cd(t_list *head)
{
	int	status;

	if (!head || !head->next)
		return(-1);
	status = 0;
	head = head->next;
	while (head->next && strcmp(head->content, " ") == 0)
		head = head->next;
	// status = directory_exists(head->content);
	// if (status < 0)
	// 	return (status);
	status = chdir(case_home(head->content));
	return (status);
}
