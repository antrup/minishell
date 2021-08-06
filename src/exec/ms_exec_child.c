/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:49:03 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/06 21:40:22 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static void	child_ex(t_command *cmd)
{
	int	test;

	if (cmd->cmd[0] != '/')
	{
		test = -1;
		errno = 2;
	}
	else
		test = execve(cmd->cmd, cmd->args, cmd->argve);
	if (test == -1)
	{
		write(2, "minishell: ", 11);
		if (errno == 2)
		{
			write(2, cmd->errname, ft_strlen(cmd->errname));
			write(2, ": command not found\n", 20);
			exit (1);
		}
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit (1);
	}
}

static void	ms_exec_error(t_command *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd->error_file_name, ft_strlen(cmd->error_file_name));
	write(2, ": ", 2);
	write(2, strerror(cmd->error), ft_strlen(strerror(cmd->error)));
	write(2, "\n", 1);
	exit (1);
}

static void	child_redir(t_command *cmd, int pipIN, int pipOUT)
{
	if (cmd->redirOUT)
	{
		dup2(cmd->OUTfd, 1);
		if (pipOUT != 1)
			close(pipOUT);
	}
	else if (pipOUT != 1)
	{	
		dup2(pipOUT, 1);
		close(pipOUT);
	}
	if (cmd->redirIN)
	{	
		dup2(cmd->INfd, 0);
		if (pipIN)
			close(pipIN);
	}
	else if (pipIN)
	{	
		dup2(pipIN, 0);
		close(pipIN);
	}
	return ;
}

int	child(t_command *cmd, int pipIN, int pipOUT)
{
	child_redir(cmd, pipIN, pipOUT);
	if (cmd->error)
		ms_exec_error(cmd);
	if (cmd->buildin)
		return (ms_exec_bd(cmd->buildin, cmd->args));
	child_ex(cmd);
	return (0);
}
