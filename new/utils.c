#include "minishell.h"

size_t	ft_strlen(const char *__s)
{
	size_t	i;

	i = 0;
	if (!__s)
		return (0);
	while (__s[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlen_var(const char *__s)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (__s[i] != '\0' && __s[i] != '=')
		i++;
	j = i;
	// in case there is spaces after the variable
	while (j-- && __s[j] == ' ')
		k++;
	if (i > 1 && (__s[i] == '=' && __s[i - 1] == '+'))
		i--;
	return (i - k);
}

char	*ft_strdup(const char *s1)
{
	char	*ret;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	ret = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (!ret)
		return (NULL);
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ret;

	i = -1;
	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	ret = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!ret)
		return (NULL);
	while (s1[++i] != '\0')
		ret[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		ret[i + j] = s2[j];
	ret[i + j] = '\0';
	return (ret);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*one;
	unsigned char	*two;

	i = 0;
	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	if (!s1 || !s2 )
		return (-1);
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (one[i] == '\0' && two[i] == '\0')
			break ;
		if ((one[i] == '\0' && two[i] != '\0') || (one[i] - two[i] < 0))
			return (-1);
		else if ((one[i] != '\0' && two[i] == '\0') || (one[i] - two[i] > 0))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ret;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
	{
		len = ft_strlen(s);
		if (len > start)
			len = ft_strlen(s + start);
	}
	ret = (char *)malloc(len * sizeof(char) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
		while (i < len)
			ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}

void	ft_free(char *s1, char *s2, char **array1, char **array2)
{
	int	i;

	i = 0;
	if (s1)
		(free(s1), s1 = NULL);
	if (s2)
		(free(s2), s2 = NULL);
	if (array1)
	{
		while (array1[i] != NULL)
			(free(array1[i]), array1[i++] = NULL);
		(free(array1), array1 = NULL);
	}
	if (array2)
	{
		while (array2[i] != NULL)
			(free(array2[i]), array2[i++] = NULL);
		(free(array2), array2 = NULL);
	}
	return ;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*one;
	char	*two;

	if (!dst && !src)
		return (NULL);
	one = (char *)src;
	two = (char *)dst;
	i = 0;
	while (i < n)
	{
		two[i] = one[i];
		i++;
	}
	dst = (void *)two;
	return (dst);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*one;
	unsigned char	*two;

	i = 0;
	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	while (one[i] != '\0' && two[i] != '\0')
	{
		if ((one[i] == '\0' && two[i] != '\0') || (one[i] - two[i] < 0))
			return (one[i] - two[i]);
		else if ((one[i] != '\0' && two[i] == '\0') || (one[i] - two[i] > 0))
			return (one[i] - two[i]);
		i++;
	}
	if (one[i] != '\0' || two[i] != '\0')
		return (one[i] - two[i]);
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	size;

	size = ft_strlen(src);
	if (dstsize == 0)
		return (size);
	i = -1;
	while (++i < dstsize - 1 && src[i] != '\0')
		dst[i] = src[i];
	dst[i] = '\0';
	return (size);
}
