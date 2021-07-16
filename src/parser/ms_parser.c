/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:52:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/08 18:08:27 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

t_node	*create_command(t_tlist *tlist)
{
	t_node		*new_node;
	t_command	*new_command;
	char		*file;
	int		buildin;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_command = malloc(sizeof(t_command));
	if (!new_command)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = COMMAND;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->data = new_command;
	new_command->cmd = NULL;
	new_command->buildin = 0;
	new_command->args = NULL;
	new_command->redirIN = 0;
	new_command->redirOUT = 0;
	new_command->INfd = 0;
	new_command->delimiter = NULL;
	new_command->OUTfd = 1;

	while (tlist)
	{
		if (tlist->tk.type == REDIR_IN)
		{
			if (tlist->next->tk.type != WORD)
				return (error_syntax_NULL(tlist->next, &new_node));
			new_command->redirIN = 1;
			file = ms_format_file(tlist->next->tk.value);
			new_command->INfd = open(file, O_RDONLY);
			free(file);
			if (INfd < 0)
			{
				free(new_command);
				free(new_node);
				return (error_open(tlist->next));
			}		
			tlist = tlist->next->next;
		}
	//	if (tlist->tk.type == REDIR_IN_A)
	//	{
	//		if (tlist->next->tk.type != WORD)
	//			return (error_syntax_NULL(tlist->next, &new_node));
	//		new_command->redirIN = 2;
	//		new_command->delimiter = tlist->next->
		if (tlist->tk.type == WORD)
		{
			if (new_command->cmd == NULL)
			{
				buildin = ms_check_buildin(tlist->tk.value)
				if (buildin)
				{
					new_command->buildin = buildin;
					new_command->cmd = tlist->tk.value;

int	ms_parser(t_ms *data)
{
	t_tlist		*current;
	int			count;
	t_node		*head;

	current = data->tlist;
	if (current.tk.type != WORD && current.tk.type != REDIR_IN 
		&& current.tk.type != REDIR_OUT && current.tk.type != REDIR_IN_A
		&& current.tk.type != REDIR_OUT_A)
		return (error_syntax(current));
	count = 0;
	while (current)
	{
		if (current.tk.type == OP_PIPE || current.tk.type == OP_AND
			|| current.tk.type == OP_OR)
			count++;
		current = current->next;
	}
	if (!count)
		head = create_command(data->tlist);
	else
	{
		head = create_tree(data, count);
