#include "minishell.h"
#include <time.h>

// unsigned int custom_rand(unsigned int custom_seed) {
//     custom_seed = custom_seed * 1103515245 + 12345;
//     return (custom_seed / 65536) % 32768;
// }

// int generate_random_number(int start, int end, unsigned int custom_seed) {
//     int range = end - start + 1;
//     int random_number = custom_rand(custom_seed) % range + start;
//     return random_number;
// }

// int main() {
// 	unsigned int custom_seed = 123456789;
// 	int	num[10] = {1234567, 9273742, 7529327, 3940293, 2846035, 5497861, 2058749, 3986577, 4023698, 1032050};
// 	int	i = 0;
//     int random_number;;
// 	while (1)
// 	{
// 		if (i == 9)
// 			i = 0;
// 		random_number = generate_random_number(1, 100000, custom_seed);
//     	printf("%d\n", random_number);
// 		custom_seed = (random_number * num[i]) + (num[i]);
// 		i++;
// 		sleep(1);
// 	}

// 	t_envp	x;
// 	t_utils	*u;
// 	t_exp	*p;

// 	u = x.
//     return 0;
// }

void	ft_error(int status, int code)
{
	if (status == -1)
		return (perror("Error "), exit(code));
}

void	ft_error_ptr(void *status, int code)
{
	if (status == NULL)
		return (perror("Error "), exit(code));
}

void	print_num()
{
	static int	i;

	if (i == 0)
	{
		i = 10;
	}
	printf("%d\n", i);
	i++;
}

int main()
{
	// char	 command[100] = "clear-";
	// char	**one = NULL;
	// char	**two = NULL;

	// ft_error(access(command, F_OK), 127);
	// char	s[100] = "hello world";

	// printf("%s\n", s);
	// // for (int i = 5; s[i]; i++)
	// 	// s[i] = '\0';
	// s[5] = '\0';
	// char *g = s;
	// printf("%s\n", s);
	// printf("%c\n", g[7]);

	int i = 0;
	while (i < 10)
	{
		print_num();
		i++;
	}
}
