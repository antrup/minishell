/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:52:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/20 13:42:52 by sshakya          ###   ########.fr       */
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

int	ms_init_parser(t_node **node, t_command **command)
{
	*node = malloc(sizeof(t_node));
	if (*node == NULL)
		return (NULL);
	*command = malloc(sizeof(t_command));
	if (*command == NULL)
	{
		free(*node);
		return (NULL);
	}
	node->type = COMMAND;
	node->left = NULL;
	node->right = NULL;
	node->data = new_command;
	command->cmd = NULL;
	command->buildin = 0;
	command->args = NULL;
	command->redirIN = 0;
	command->redirOUT = 0;
	command->INfd = 0;
	command->delimiter = NULL;
	command->OUTfd = 1;
}

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
		while (*token && (*token)->tk.type == WORD)
		{
			command->args[i] = current->tk.value;
			*token = (*token)->next;
		}
	}
}

t_node	*create_command(t_tlist *tlist)
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
	}
}
