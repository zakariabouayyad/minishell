/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:44:35 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 11:50:26 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*show_prompt(t_envp *env_lst)
{
	char	*line_read;
	char	*str;
	char	*tmp1;
	char	*tmp2;

	line_read = NULL;
	str = getcwd(NULL, PATH_MAX);
	tmp1 = ft_strjoin(BBLUE, str);
	free(str);
	tmp2 = ft_strjoin(tmp1, " \x1B[1;33m✗ \x1B[0m");
	// if (line_read)
		// free(line_read);
	line_read = readline(tmp2);
	if (line_read == NULL)
		return (NULL);
	ft_free(tmp1, tmp2, NULL, NULL);
	if (line_read != NULL && line_read[0] != '\0')
		add_history(line_read);
	return (line_read);
}

void	signint_handler(int signal)
{
	if (signal == SIGQUIT)
		return ;
	g_status = 1;
	if (waitpid(-1, NULL, WNOHANG) != -1)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_control_d(t_envp **env_lst)
{
	free_lst(env_lst);
	write(STDOUT_FILENO, "exit\n", 6);
	exit(0);
}

void	init(t_envp **env_lst, char **envp)
{
	rl_catch_signals = 0;
	g_status = 0;
	make_env_list(envp, env_lst);
	signal(SIGINT, signint_handler);
	signal(SIGQUIT, signint_handler);
}

int	main(int ac, char *av[], char *envp[])
{
	t_envp	*env_lst;

	(void)ac;
	(void)av;
	env_lst = NULL;
	init(&env_lst, envp);
	ft_minishell(&env_lst);
}
