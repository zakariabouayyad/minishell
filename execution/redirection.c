/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:56:29 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 02:06:10 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc(char *lim)
{
	int		tmp;
	char	*buf;
	char	*str;

	tmp = open(".heredoc", O_CREAT | O_RDWR, 0600);
	buf = readline("> ");
	if (!buf)
		unlink(".heredoc");
	while (ft_strcmp(lim, buf) != 0)
	{
		write(tmp, buf, ft_strlen(buf));
		write(tmp, "\n", 1);
		buf = readline("> ");
		if (!buf)
			unlink(".heredoc");
	}
	close(tmp);
	tmp = open(".heredoc", O_RDWR);
	dup2(tmp, STDIN_FILENO);
	close(tmp);
	unlink(".heredoc");
}

void	the_redir_cases(t_tree *node, int infile, int outfile)
{
	if (node->redirection->type == OUTPUT)
	{
		outfile = open(node->redirection->next->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(outfile, STDOUT_FILENO);
	}
	else if (node->redirection->type == OUTPUT_APPEND)
	{
		outfile = open(node->redirection->next->content,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(outfile, STDOUT_FILENO);
	}
	else if (node->redirection->type == INPUT)
	{
		infile = open(node->redirection->next->content, O_RDONLY);
		dup2(infile, STDIN_FILENO);
	}
	else if (node->redirection->type == HERE_DOC)
		heredoc(node->redirection->next->content);
}

int	rederection_case(t_tree *node, int in, int out)
{
	int	outfile;
	int	infile;

	while (node->redirection)
	{
		the_redir_cases(node, infile, outfile);
		node->redirection = node->redirection->next;
	}
	return (0);
}
