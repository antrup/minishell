/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:52:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/25 17:03:34 by toni             ###   ########.fr       */
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

int		ms_count_args(t_tlist *tokens)
{
	t_tlist	*current;
	int		i;

	i = 0;
	current = tokens;
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
		return (errno);
	*command = malloc(sizeof(t_command));
	if (*command == NULL)
	{
		free(*node);
		return (errno);
	}
	(*node)->type = NO_CMD;
	(*node)->left = NULL;
	(*node)->right = NULL;
	(*node)->data = *command;
	(*command)->cmd = NULL;
	(*command)->buildin = 0;
	(*command)->args = NULL;
	(*command)->redirIN = 0;
	(*command)->redirOUT = 0;
	(*command)->INfd = 0;
	(*command)->delimiter = NULL;
	(*command)->OUTfd = 1;
	return (0);
}

//t_tlist *ms_cut_tlist(t_tlist *tokens, int start, int end)
//{
//	t_tlist		*cmd_tokens;
//	t_tlist		*current;
//	int			nb;
//
//	nb = end - start;
//	current = tokens;
//	cmd_tokens = malloc(sizeof(t_tlist));
//	while (start)
//	{
//		current = current->next;
//		start--;
//	}
//	while (nb)
//	{
//		new_tokens = malloc(sizeof(t_tlist));
//		if (!new_tokens)
//			return (NULL);
//		new_token->tk.type = current->tk.type;
//		new_token->tk.value = current->tk.value;
//		new_token->previous = current_new;
//		current_new->next = new_token;
//		new_token->next = NULL;
//		new->token = NULL;
//		current = current->next;


t_node	*ms_new_tree(t_tlist *tokens, int count)
{
	t_tlist		*current;
	t_node		*head;
	
	head = malloc(sizeof(t_node));
	if (!head)
		return (NULL);
	head->type = NO_PIPE;
	head->left = ms_create_cmd(tokens);
	current = tokens;
	while (current->tk.type != OP_PIPE)
		current = current->next;
	current = current->next;
	if (!current || current->tk.type == OP_PIPE)
		return (NULL); //ERR_SYN
	if (count == 1)
		head->right = ms_create_cmd(current);
	else
	{	
		count--;
		head->right = ms_new_tree(current, count);
	}
	if (head->right == NULL)
	{
		free(head->left);
		free(head);
		head = NULL;
	}
	return (head);
}

int	ms_parser(t_tlist *tokens, t_node **thead)
{
	t_tlist		*current;
	int			count;

	current = tokens;
	if (current == NULL)
		return (0);
	if (current->tk.type != WORD && current->tk.type != REDIR_IN 
			&& current->tk.type != REDIR_OUT && current->tk.type != REDIR_IN_A
			&& current->tk.type != REDIR_OUT_A)
		return (ERR_SYN);
	count = 0;
	while (current)
	{
		if (current->tk.type == OP_PIPE)
			count++;
		current = current->next;
	}
	if (!count)
		*thead = ms_create_cmd(tokens);
	if (count)
		*thead = ms_new_tree(tokens, count);
	return (0);
}
