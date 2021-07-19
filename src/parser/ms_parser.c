/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:52:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/19 21:05:04 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_check_buildin(char *cmd)
{
	int ret;

	ret = 0;
	ret = ft_strcmp(cmd, "echo");
	if (ret)
		return (BI_ECHO);	
	ft_strcmp(cmd, "cd");
	if (ret)
		return (BI_CD);
	ft_strcmp(cmd, "pwd");
	if (ret)
		return (BI_PWD);	
	ft_strcmp(cmd, "export");
	if (ret)
		return (BI_EXPORT);	
	ft_strcmp(cmd, "unset");
	if (ret)
		return (BI_UNSET);	
	ft_strcmp(cmd, "env");
	if (ret)
		return (BI_ENV);	
	ft_strcmp(cmd, "exit");
	if (ret)
		return (BI_EXIT);
	return (0);
}

int		ms_count_args(t_tlist *tlist)
{
	t_tlist	*current;
	int		i;
	
	i = 0;
	current = tlist;
	while (current && current->tk.type == WORD)
	{	
		i++;
		current = current->next;
	}
	return (i);
}

t_node	*create_command(t_tlist *tlist)
{
	t_node		*new_node;
	t_command	*new_command;
	char		*file;
	int		buildin;
	t_tlist	*current;
	int		i;

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
	current = tlist;
	while (current && current->tk.type != OP_PIPE && current->tk.type != OP_AND && current->tk.type != OP_OR)
	{
		if (current->tk.type == REDIR_IN)
		{
			if (current->next->tk.type != WORD)
				return (error_syntax_NULL(current->next, &new_node));
			new_command->redirIN = 1;
			file = ms_format_file(current->next->tk.value);
			new_command->INfd = open(file, O_RDONLY);
			free(file);
			if (INfd < 0)
			{
				free(new_command);
				free(new_node);
				return (error_open(current->next));
			}		
			current = current->next->next;
		}
		if (current->tk.type == REDIR_OUT)
		{
			if (current->next->tk.type != WORD)
				return (error_syntax_NULL(current->next, &new_node));
			new_command->redirOUT = 1;
			file = ms_format_file(current->next->tk.value);
			new_command->INfd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			free(file);
			if (INfd < 0)
			{
				free(new_command);
				free(new_node);
				return (error_open(current->next));
			}		
			current = current->next->next;
		}
		if (current->tk.type == REDIR_OUT_A)
		{
			if (current->next->tk.type != WORD)
				return (error_syntax_NULL(current->next, &new_node));
			new_command->redirOUT = 1;
			file = ms_format_file(current->next->tk.value);
			new_command->INfd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			free(file);
			if (INfd < 0)
			{
				free(new_command);
				free(new_node);
				return (error_open(current->next));
			}		
			current = current->next->next;
		}
	//	if (tlist->tk.type == REDIR_IN_A)
	//	if (tlist->tk.type == REDIR_IN_A)
	//	if (tlist->tk.type == REDIR_IN_A)
	//	{
	//		if (tlist->next->tk.type != WORD)
	//			return (error_syntax_NULL(tlist->next, &new_node));
	//		new_command->redirIN = 2;
	//		new_command->delimiter = tlist->next->
		if (current->tk.type == WORD)
		{
			if (new_command->cmd == NULL)
			{
				buildin = ms_check_buildin(current->tk.value);
				if (buildin)
				{
					new_command->buildin = buildin;
					new_command->cmd = current->tk.value;
				}
				else
					new_command->cmd = ms_format_cmd(current->tk.value);
				current = current->next;
				i = 0;
				if (current->tk.type == WORD)
					new_command->args(malloc(sizeof(char *) * ms_count_args(current) + 1));
				while (current && current->tk.type == WORD)
				{
					new_command_args[i] = current->tk.value;
					current->current->next;
				}
			}
		}
int	ms_parser(t_ms *data)

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
