/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_ina.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 00:14:38 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/01 19:12:57 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static size_t	ms_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static void	ms_join(char *buff, char *line, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buff && buff[i] != '\0')
	{
		str[i] = buff[i];
		i++;
	}
	str[i] = '\n';
	j = 0;
	i++;
	while (line[j] != '\0')
	{
		str[i] = line[j];
		i++;
		j++;
	}
	str[i] = '\0';
}

static char	*ms_strjoin(char *buff, char *line)
{
	char	*str;
	size_t	len;

	if (!buff)
	{	
		str = ft_strdup(line);
		free(line);
		return (str);
	}
	len = ms_strlen(buff) + ms_strlen(line);
	str = malloc(sizeof(char) * (len + 2));
	if (str == NULL)
		return (NULL);
	ms_join(buff, line, str);
	free(buff);
	free(line);
	return (str);
}

static int ms_write_heredoc(char *end, int *fd)
{
	char	*line;
	char	*buff;
	int		eof;

	buff = NULL;
	line = NULL;
	eof = EOF;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return (ERR_REDIR_IN);
		if (ft_strcmp(line, end))
			break ;
		buff = ms_strjoin(buff, line);
		if (buff == NULL)
			return (errno);
	}
	ft_putstr_fd(buff, fd[1]);
	ft_putchar_fd('\n', fd[1]);
	write(fd[1], &eof, 1);
	free(buff);
	free(line);
	close(fd[1]);
	return (0);
}

static int	ms_fork_redir(char *end)
{
	int	error;
	int	fd[2];
	pid_t pid;

	error = 0;
	if (end == NULL)
		return (0);
	if (pipe(fd) == -1)
		return (ERR_PIPE);
	g_shell.rda_fd[0] = fd[0];
	g_shell.rda_fd[1] = fd[1];
	pid = fork();
	if (pid == -1)
		return (ERR_REDIR_IN);
	if (pid == 0)
	{
		g_shell.rda = 1;
		error = ms_write_heredoc(end, fd);
		printf("fork fd = %d\n", fd[0]);
		printf("fork pid = %d\n", pid);
		exit(0);
	}
	wait(NULL);
	close(fd[1]);
	printf("fork fd = %d\n", fd[0]);
	return (fd[0]);
}

int	ms_redir_ina(t_tlist **token, t_command *command)
{
	char	*end;

	if (!(*token)->next || (*token)->next->tk.type != WORD)
		return (ERR_SYN);
	*token = (*token)->next;
	end = (*token)->tk.value;
	command->redirIN = 1;
	command->INfd = ms_fork_redir(end);
	printf("infd = %d\n", command->INfd);
	*token = (*token)->next;
	return (0);
}
