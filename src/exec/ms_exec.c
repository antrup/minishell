/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:19:21 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/27 14:59:32 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static void child_ex(char *cmd, char **argve, char **argv)
{
	int test;

	test = execve(cmd, argv, argve);
	if (test == -1)
		printf("error");
}

static int child(t_command *cmd, int pipIN, int pipOUT)
{
	if (isatty(cmd->INfd))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGTERM, SIG_DFL);
	}
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
	child_ex(cmd->cmd, cmd->argve, cmd->args);
	return (0);
}

int	ms_exec(t_node *head, int pipIN)
{
	int		pip[2];
	int		test;
	pid_t	pid;

	test = 0;
	if (!head)
		return (1);
	if (head->type == NO_CMD)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			return (child(head->data, pipIN, 0));
		head->pid = pid;
		wait(NULL);
		return (0);
	}
	if (head->type == NO_PIPE)
	{	
		test = pipe(pip);
		pid = fork();
		if (test == -1 || pid == -1)
			return (-1);
		if (pid == 0)
			return (child(head->left->data, pipIN, pip[1]));
		wait(NULL);
		close(pip[1]);
		ms_exec(head->right, pip[0]);
	}
	return (0);
}	
