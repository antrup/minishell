/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_create_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:52:40 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/04 22:53:16 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_redir_in(t_tlist **token, t_command *command)
{
	char	*file;

	file = NULL;
	if (command->error)
	{
		*token = (*token)->next->next;
		return (0);
	}
	command->redir_in = 1;
	file = ms_format_file((*token)->next->tk.value);
	command->in_fd = open(file, O_RDONLY);
	free(file);
	if (command->in_fd < 0)
	{	
		command->error = errno;
		command->error_file_name = (*token)->next->tk.value;
	}
	*token = (*token)->next->next;
	return (0);
}

int	ms_redir_out(t_tlist **token, t_command *command)
{
	char	*file;

	file = NULL;
	if (command->error)
	{
		*token = (*token)->next->next;
		return (0);
	}
	command->redir_out = 1;
	file = ms_format_file((*token)->next->tk.value);
	command->out_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file);
	if (command->out_fd < 0)
	{	
		command->error = errno;
		command->error_file_name = (*token)->next->tk.value;
	}
	*token = (*token)->next->next;
	return (0);
}

int	ms_redir_outa(t_tlist **token, t_command *command)
{
	char	*file;

	file = NULL;
	if ((*token)->next->tk.type != WORD)
		return (ERR_SYN);
	command->redir_out = 1;
	file = ms_format_file((*token)->next->tk.value);
	command->in_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(file);
	if (command->in_fd < 0)
		return (ERR_OPEN);
	*token = (*token)->next->next;
	return (0);
}
