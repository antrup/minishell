/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:46:44 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/10 19:14:35 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_isexec_buildin(t_node *head)
{
	if (head->data->buildin == BI_CD || head->data->buildin == BI_EXPORT
		|| head->data->buildin == BI_UNSET || head->data->buildin == BI_EXIT
		|| head->data->buildin == BI_ENV)
		return (1);
	return (0);
}

int	ms_exec_bd(int	bd, char **args)
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
		return (ms_exit(&(args[1])));
	if (bd == BI_ENV)
		return (ms_env());
	return (0);
}

void	ms_close_fds(t_command *cmd, int pipIN)
{
	if (cmd->in_fd && cmd->redir_in)
		close(cmd->in_fd);
	if (cmd->redir_out)
		close(cmd->out_fd);
	if (pipIN)
		close(pipIN);
}

void	ms_wait_children(t_node *current, int *error)
{
	int	status;

	if (current->type == NO_CMD)
	{
		waitpid(current->pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			*error = WEXITSTATUS(status);
		else
			*error = 1;
		return ;
	}
	else
	{
		waitpid(current->left->pid, &status, 0);
		ms_wait_children(current->right, error);
		return ;
	}
}
