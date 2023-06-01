#include "minishell.h"

static size_t	word_count(char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			++count;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static int	*ft_splitchr(char *s, int c)
{
	int	*i;

	i = (int *)malloc(2 * sizeof(int));
	i[0] = -1;
	while (s[++i[0]] != '\0' && s[i[0]] != c)
		;
	i[1] = i[0];
	while (s[i[1]] != '\0' && s[i[1]++] == c)
		;
	i[1]--;
	return (i);
}

static void	*fail(char **array, int i)
{
	while (i >= 0)
	{
		free(array[i]);
		array[i] = NULL;
		i--;
	}
	free(array);
	array = NULL;
	return (NULL);
}

static char	**creat_array(char *s, char **array, size_t count, char c)
{
	int	i;
	int	*tmp;

	i = -1;
	while (*s == c)
		s++;
	while (count--)
	{
		tmp = ft_splitchr(s, c);
		if (tmp[0] != 0)
		{
			array[++i] = ft_substr(s, 0, tmp[0]);
			if (!array[i])
				return (fail(array, i));
			s += tmp[1];
		}
		else
			array[++i] = ft_substr(s, 0, ft_strlen(s));
		free(tmp);
	}
	array[++i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**array;

	if (!s)
		return (NULL);
	count = word_count((char *)s, c);
	array = (char **)malloc((count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (creat_array((char *)s, array, count, c) == NULL)
		return (NULL);
	return (array);
}