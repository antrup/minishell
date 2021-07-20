/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_create_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:44:45 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/20 13:46:51 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_redir_in(t_tlist **token, t_node *node, t_command *command)
{
	char *file;

	file = NULL;
	if ((*token)->next->tk.type != WORD)
		return (ERR_SYN);
	command->redirIn = 1;
	file = ms_format_file((*token)->next->tk.value);
	command->INfd = open(file, O_RDONLY);
	free(file);
	if (command->INfd < 0)
		return (ERR_OPEN);
	*token = (*token)->next;
}

static int	ms_redir_out(t_tlist **token, t_node *node, t_command *command)
{
	char *file;

	file = NULL;
	if ((*token)->next->tk.type != WORD)
		return (ERR_SYN);
	command->redirOUT = 1;
	file = ms_format_file((*token)->next->tk.value);
	new_command->INfd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file);
	if (INfd < 0)
		return (ERR_OPEN);
	*token = (*token)->next->next;
}

static int	ms_redir_outa(t_tlist **token, t_node *node, t_command *command)
{
	char *file;

	file = NULL;
	if ((*token)->next->tk.type != WORD)
		return (ERR_SYN);
	command->redirOUT = 1;
	file = ms_format_file(current->next->tk.value);
	command->INfd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(file);
	if (INfd < 0)
		return (ERR_OPEN);
	*token = (*token)->next->next;
}

static int	ms_cmd(t_tlist **token, t_node *node, t_command *command)
{
	int		buildin;
	int		i;

	buildin = 0;
	i = 0;
	if (command->cmd == NULL)
	{
		buildin = ms_check_buildin((*token)->tk.value);
		if (buildin)
		{
			command->buildin = buildin;
			command->cmd = current->tk.value;
		}
		else
			command->cmd = ms_format_cmd(current->tk.value);
		*token = (*token)->next;
		if ((*token)->tk.type == WORD)
			command->args(malloc(sizeof(char *) * ms_count_args(*token) + 1));
		if (command->args == NULL)
			return (ERR_MEM);
		while (*token && (*token)->tk.type == WORD)
		{
			command->args[i] = current->tk.value;
			*token = (*token)->next;
		}
	}
}

t_node	*ms_create_cmd(t_tlist *tlist)
{
	t_node		*new_node;
	t_command	*new_command;
	t_tlist	*current;

	ms_init_parser(&new_node, &new_command);
	current = tlist;
	while (current && current->tk.type != OP_PIPE
			&& current->tk.type != OP_AND
			&& current->tk.type != OP_OR)
	{
		if (current->tk.type == REDIR_IN)
			ms_redir_in(&current, new_node, new_command);
		if (current->tk.type == REDIR_OUT)
			ms_redir_out(&current, new_node, new_command);
		if (current->tk.type == REDIR_OUT_A)
			ms_redir_outa(&current, new_node, new_command);
		//	
		//	if (tlist->tk.type == REDIR_IN_A)
		//	if (tlist->tk.type == REDIR_IN_A)
		//	if (tlist->tk.type == REDIR_IN_A)
		//	{
		//		if (tlist->next->tk.type != WORD)
		//			return (error_syntax_NULL(tlist->next, &new_node));
		//		new_command->redirIN = 2;
		//		new_command->delimiter = tlist->next->
		if (current->tk.type == WORD)
			ms_cmd(&current, new_node, new_command);
	}
}
