/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:19:21 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/04 18:29:10 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_exec_pipe(t_node *head, int pipIN)
{
	int		pip[2];
	int		test;
	int		error;
	pid_t	pid;

	test = 0;
	error = 0;
	test = pipe(pip);
	if (test == -1)
		return (errno);
	pid = fork();
	head->left->pid = pid;
	if (pid == -1)
		return (errno);
	if (pid == 0)
		return (child(head->left->data, pipIN, pip[1]));
	close(pip[1]);
	if (error)
		return (error);
	error = ms_exec(head->right, pip[0]);
	return (error);
}

static int	ms_exec_cmd(t_node *head, int pipIN)
{		
	int		test;
	int		error;
	pid_t	pid;	

	test = 0;
	error = 0;
	if (head->data->cmd)
	{
		if (ms_isexec_buildin(head))
			error = ms_exec_bd(head->data->buildin, head->data->args);
		else
		{
			pid = fork();
			head->pid = pid;
			if (pid == -1)
				return (errno);
			if (pid == 0)
				return (child(head->data, pipIN, 0));
			ms_wait_children(g_shell.data->thead, &error);
		}
	}
	return (0);
}

int	ms_exec(t_node *head, int pipIN)
{
	int		error;

	error = 0;
	if (!head)
		return (1);
	if (head->type == NO_CMD)
	{
		if (head->data->cmd)
			error = ms_exec_cmd(head, pipIN);
		ms_close_fds(head->data, pipIN);
		return (error);
	}
	if (head->type == NO_PIPE)
		error = ms_exec_pipe(head, pipIN);
	return (error);
}
