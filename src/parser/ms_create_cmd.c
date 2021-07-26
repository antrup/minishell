/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_create_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:44:45 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/26 17:10:19 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_redir_in(t_tlist **token, t_command *command)
{
	char	*file;

	file = NULL;
	if ((*token)->next->tk.type != WORD)
		return (ERR_SYN);
	command->redirIN = 1;
	file = ms_format_file((*token)->next->tk.value);
	command->INfd = open(file, O_RDONLY);
	free(file);
	if (command->INfd < 0)
		return (ERR_OPEN);
	*token = (*token)->next->next;
	return (0);
}

static int	ms_redir_out(t_tlist **token, t_command *command)
{
	char	*file;

	file = NULL;
	if ((*token)->next->tk.type != WORD)
		return (ERR_SYN);
	command->redirOUT = 1;
	file = ms_format_file((*token)->next->tk.value);
	command->OUTfd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file);
	if (command->INfd < 0)
		return (ERR_OPEN);
	*token = (*token)->next->next;
	return (0);
}

static int	ms_redir_outa(t_tlist **token, t_command *command)
{
	char	*file;

	file = NULL;
	if ((*token)->next->tk.type != WORD)
		return (ERR_SYN);
	command->redirOUT = 1;
	file = ms_format_file((*token)->next->tk.value);
	command->INfd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(file);
	if (command->INfd < 0)
		return (ERR_OPEN);
	*token = (*token)->next->next;
	return (0);
}

static int	ms_cmd(t_tlist **token, t_command *command)
{
	int		buildin;
	int		i;

	buildin = 0;
	i = 0;
	if ((*token)->tk.type == P_OPEN)
	{
		*token = (*token)->next;
		return (0);
	}
	if ((*token)->tk.type == P_CLOSE)
	{
		*token = (*token)->next;
		return (0);
	}
	if (command->cmd == NULL)
	{
		buildin = ms_check_buildin((*token)->tk.value);
		if (buildin)
		{
			command->buildin = buildin;
			command->cmd = ft_strdup((*token)->tk.value);
		}
		else
			command->cmd = ms_format_cmd((*token)->tk.value);
		*token = (*token)->next;
		if ((*token) == NULL)
			return (0);
		if ((*token)->tk.type == WORD)
			command->args = malloc(sizeof(char *) * ms_count_args(*token) + 1);
		if (command->args == NULL)
			return (errno);
		while (*token && (*token)->tk.type == WORD)
		{
			command->args[i] = ft_strdup((*token)->tk.value);
			*token = (*token)->next;
			i++;
		}
		command->args[i] = NULL;
	}
	return (0);
}

t_node	*ms_create_cmd(t_tlist *tlist)
{
	t_node		*new_node;
	t_command	*new_command;
	t_tlist		*current;

	ms_init_parser(&new_node, &new_command);
	current = tlist;
	while (current && current->tk.type != OP_PIPE && current->tk.type != OP_AND
		&& current->tk.type != OP_OR)
	{
		if (current->tk.type == REDIR_IN)
			ms_redir_in(&current, new_command);
		else if (current->tk.type == REDIR_OUT)
			ms_redir_out(&current, new_command);
		else if (current->tk.type == REDIR_OUT_A)
			ms_redir_outa(&current, new_command);
		else if (current->tk.type == REDIR_IN_A)
			ms_redir_ina(&current, new_command);
		else if (current->tk.type == WORD
			|| (current->tk.type == P_OPEN || current->tk.type == P_CLOSE))
			ms_cmd(&current, new_command);
		else if (current->tk.type == OP_OR)
			current = current->next;
	}
	return (new_node);
}
