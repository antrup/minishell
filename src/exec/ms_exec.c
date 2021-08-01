/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:19:21 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/01 18:23:03 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static void child_ex(char *cmd, char **argve, char **argv)
{
	int test;

	test = execve(cmd, argv, argve);
	if (test == -1)
		printf(" Exec error\n");
}

int ms_exec_bd(int	bd, char **args)
{
	if (bd == BI_CD)
		return (ms_cd(&(args[1])));
	if (bd == BI_ECHO)
		exit(ms_echo(&(args[1])));
	if (bd == BI_PWD)
		exit(ms_pwd());
	if (bd == BI_EXPORT)
		return (ms_export(&(args[1])));
	if (bd == BI_UNSET)
		return (ms_unset(&(args[1])));
	if (bd == BI_EXIT)
	{
		ms_clean(g_shell.data);
		exit(0);
	}
	return (0);
}

static int child(t_command *cmd, int pipIN, int pipOUT)
{
	if (cmd->redirOUT)
	{
		dup2(cmd->OUTfd, 1);
		if (pipOUT)
			close(pipOUT);
	}
	else if (pipOUT)
		dup2(pipOUT, 1);
	if (pipOUT)
		dup2(pipOUT, 1);
	if (cmd->redirIN)
	{	
		dup2(cmd->INfd, 0);
		if (pipIN)
			close(pipIN);	
	}
	else if (pipIN)
		dup2(pipIN, 0);
	if (cmd->buildin)
		return(ms_exec_bd(cmd->buildin, cmd->args));
	child_ex(cmd->cmd, cmd->argve, cmd->args);
	return (0);
}

void	ms_close_fds(t_command *cmd, int pipIN)
{
	if (cmd->INfd)
		close(cmd->INfd);
	if (cmd->redirOUT)
		close(cmd->OUTfd);
	if (pipIN)
		close(pipIN);
}

int	ms_exec(t_node *head, int pipIN)
{
	int		pip[2];
	int		test;
	int		error;
	pid_t	pid;

	test = 0;
	error = 0;
	if (!head)
		return (1);
	if (head->type == NO_CMD)
	{
		if (head->data->cmd)
		{
			if (head->data->buildin == BI_CD || head->data->buildin == BI_EXPORT
				|| head->data->buildin == BI_UNSET || head->data->buildin == BI_EXIT)
				error = ms_exec_bd(head->data->buildin, head->data->args);
			else
			{
				pid = fork();
				if (pid == -1)
					return (errno);
				if (pid == 0)
					return (child(head->data, pipIN, 0));
				head->pid = pid;
				wait(&error);
			}
		}
		ms_close_fds(head->data, pipIN);
		return (error);
	}
	if (head->type == NO_PIPE)
	{	
		test = pipe(pip);
		if (test == -1)
			return (errno);
		pid = fork();
		if (pid == -1)
			return (errno);
		if (pid == 0)
			return (child(head->left->data, pipIN, pip[1]));
		wait(&error);
		close(pip[1]);
		if (error)
			return (error);
		error = ms_exec(head->right, pip[0]);
	}
	return (error);
}	
