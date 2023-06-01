#include "minishell.h"

static int		decrement_end(const char *s, int end, int k)
{
	int		i;

	i = 0;
	while (end >= 0)
	{
		if ((k == 1 && s[end] != '\"') // "   d"
			|| (k == 0 && (s[end] != ' ' && s[end] != '\"'))) // plpsfl
			i++;
		else if (s[end] == '\"')
		{
			if (k == 1 && s[end - 1] != ' ') //  plpsfl"   d"
				k = 0;
			else if (k == 0) // "..."....
				k = 1;
			else // plpsfl "   d"
				return (++i);
			i++;
		}
		else
			break ;
		end--;
	}
	return (i);
}

static int		check_double_cotes_sequance(const char *s, int *end)
{
	int	k;

	k = 0;
	if (s[*end] == '\"') // "lol2 c " plpsfl
	{
		(*end)--;
		k = 1;
	}
	while (*end >= 0 && (s[*end] == '\"' && s[*end - 1] != ' ')) // "   d"""""""
	{
		(*end)--;
		k++;
		if (k == 2)
			k = 0;
	}
	return (k);
}

static int		count_strings(const char *s, int end)
{
	t_utils	x;

	x.k = 0;
	x.count = 0;
	while (end >= 0)
	{
		while (end >= 0 && s[end] == ' ')
			end--;
		x.count++;
		if (end == 0)
			break ;
		x.k = check_double_cotes_sequance(s, &end);
		if (x.k == 1)
			end -= decrement_end(s, end, x.k);
		else if (x.k == 0)
			end -= decrement_end(s, end, x.k);
		x.k = 0;
	}
	return (x.count);
}

static int		*strings_lents(const char *s, int end, int count)
{
	t_utils	x;

	x.i = 0;
	x.j = 0;
	x.k = 0;
	x.count = 0;
	x.nums = (int *)malloc(count * sizeof(int));
	while (end >= 0)
	{
		x.j = end;
		while (end >= 0 && s[end] == ' ')
			end--;
		if (end == 0)
			return (x.nums);
		x.k = check_double_cotes_sequance(s, &end);
		if (x.k == 1)
			end -= decrement_end(s, end, x.k);
		else if (x.k == 0)
			end -= decrement_end(s, end, x.k);
		x.nums[x.i++] = x.j - end;
		x.k = 0;
	}
	return (x.nums);
}

char	**export_split(const char *line_read)
{
	t_utils	x;

	if (!line_read || line_read[0] == '\0')
		return (NULL);
	x.i = 0;
	x.ret = NULL;
	x.j = ft_strlen(line_read);
	x.count = count_strings(line_read, x.j);
	x.ret = (char **)malloc((x.count + 1) * sizeof(char *));
	if (!x.ret)
		printf("error allocation in export_split\n");
	x.ret[x.count] = NULL;
	x.nums = strings_lents(line_read, x.j, x.count);
	x.j = -1;
	while (x.count--)
	{
		x.ret[++x.j] = ft_substr(&line_read[x.i], 0, x.nums[x.count]);
		x.i += x.nums[x.count];
	}
	free(x.nums);
	return (x.ret);
}
