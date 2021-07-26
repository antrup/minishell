/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:02:43 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/26 14:19:37 by sshakya          ###   ########.fr       */
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

int	ms_name_sizer(char	*cmd_name)
{
	int	i;
	int	size_name;

	i = 0;
	size_name = 0;
	while (cmd_name[i] != ' ' && cmd_name[i] != '\0')
	{
		size_name++;
		i++;
	}
	return (size_name);
}
