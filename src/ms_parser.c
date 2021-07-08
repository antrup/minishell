/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:52:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/08 11:54:24 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

t_node	*create_command(t_tlist *tlist)
{
	t_node		*new_node;
	t_command	*new_command;

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
	
	if (tlist->tk.type == REDIR_IN)
	{
		if (tlist->next->tk.type != WORD)
			return (error_syntax_NULL(tlist->next, &new_node));
		
		new_command->redirIN = 1;



int	ms_parser(t_ms *data)
{
	t_tlist		*current;
	int			count;
	t_node		*head

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
