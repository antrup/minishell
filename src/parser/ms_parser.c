/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:52:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/04 18:47:43 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

t_node	*ms_new_tree(t_tlist *tokens, int count, char **env)
{
	t_tlist		*current;
	t_node		*head;

	head = malloc(sizeof(t_node));
	if (!head)
		return (NULL);
	head->type = NO_PIPE;
	head->left = ms_create_cmd(tokens, env);
	current = tokens;
	while (current->tk.type != OP_PIPE && current->tk.type != OP_AND)
		current = current->next;
	current = current->next;
	if (!current || current->tk.type == OP_PIPE)
		return (NULL);
	if (count == 1)
		head->right = ms_create_cmd(current, env);
	else
	{	
		count--;
		head->right = ms_new_tree(current, count, env);
	}
	if (head->right == NULL)
	{
		free(head->left);
		free(head);
		head = NULL;
	}
	return (head);
}

int	ms_parser(t_tlist *tokens, t_node **thead, char **env)
{
	t_tlist		*current;
	int			count;

	current = tokens;
	if (current == NULL)
		return (0);
	count = 0;
	while (current && current->tk.type != OP_AND && current->tk.type != OP_OR)
	{
		if (current->tk.type == OP_PIPE)
			count++;
		current = current->next;
	}
	if (!count)
		*thead = ms_create_cmd(tokens, env);
	if (count)
		*thead = ms_new_tree(tokens, count, env);
	return (0);
}
