/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 09:43:15 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/09 09:43:19 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static void	ms_clean_heredoc(char *buff, char *line, int *fd)
{
	ft_putstr_fd(buff, fd[1]);
	ft_putchar_fd('\n', fd[1]);
	free(buff);
	free(line);
	close(fd[1]);
}

static int	ms_write_heredoc(char *end, int *fd)
{
	char	*line;
	char	*buff;
	int		error;

	buff = NULL;
	line = NULL;
	error = 0;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ms_heredoc_error(end);
			break ;
		}
		if (ft_strcmp(line, end))
			break ;
		if (ms_hasvar(line))
			line = ms_heredoc_expand(line);
		buff = ms_heredoc_join(buff, line, &error);
		if (error)
			return (error);
	}
	ms_clean_heredoc(buff, line, fd);
	return (0);
}

static int	ms_fork_redir(char *end)
{
	int		error;
	int		fd[2];
	pid_t	pid;

	error = 0;
	if (end == NULL)
		return (0);
	if (pipe(fd) == -1)
		return (ERR_PIPE);
	g_shell.rda_fd[0] = fd[0];
	g_shell.rda = 1;
	pid = fork();
	if (pid == -1)
		return (ERR_REDIR_IN);
	g_shell.r_pid = pid;
	if (pid == 0)
	{
		error = ms_write_heredoc(end, fd);
		exit(0);
	}
	wait(NULL);
	close(fd[1]);
	g_shell.rda = 0;
	return (fd[0]);
}

int	ms_heredoc(t_tlist **token, t_command *command)
{
	char	*end;

	if (!(*token)->next || (*token)->next->tk.type != WORD)
		return (ERR_SYN);
	*token = (*token)->next;
	end = (*token)->tk.value;
	command->redir_in = 1;
	command->in_fd = ms_fork_redir(end);
	*token = (*token)->next;
	return (0);
}
