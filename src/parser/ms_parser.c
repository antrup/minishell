/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:52:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/23 15:50:09 by sshakya          ###   ########.fr       */
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
		if (current->tk.type == OP_PIPE || current->tk.type == OP_AND
				|| current->tk.type == OP_OR)
			count++;
		current = current->next;
	}
	if (!count)
		*thead = ms_create_cmd(tokens);
	return (0);
}
