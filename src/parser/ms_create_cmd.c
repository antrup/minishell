/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_create_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:44:45 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/06 17:36:35 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static void	ms_buildin(t_tlist **token, t_command *command)
{
	command->buildin = buildin;
	command->cmd = ft_strdup((*token)->tk.value);
	command->errname = ft_strdup((*token)->tk.value);
	return ;
}

static int	ms_cmd(t_tlist **token, t_command *command)
{
	int		i;

	i = 0;
	if (command->cmd == NULL)
	{
		if (ms_check_buildin((*token)->tk.value))
			ms_buildin(token, command);
		else
		{
			command->cmd = ms_format_cmd((*token)->tk.value);
			command->errname = ft_strdup((*token)->tk.value);
		}
		command->args = malloc(sizeof(char *) * (ms_count_args(*token) + 2));
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

static int	ms_subshell(t_tlist **token, t_command *command)
{
	command->cmd = ms_format_cmd(g_shell.mypath);
	command->args = malloc(sizeof(char *) * (ms_count_args(*token) + 3));
	if (command->args == NULL)
		return (errno);
	command->args[0] = ft_strdup(command->cmd);
	command->args[1] = ft_strdup((*token)->tk.value);
	command->args[2] = NULL;
	*token = (*token)->next;
	return (0);
}

t_node	*ms_create_cmd(t_tlist *tlist, char **env)
{
	t_node		*new_node;
	t_command	*new_command;
	t_tlist		*current;

	ms_init_parser(&new_node, &new_command, env);
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
			ms_heredoc(&current, new_command);
		else if (current->tk.type == WORD)
			ms_cmd(&current, new_command);
		else if (current->tk.type == OP_PAREN)
			ms_subshell(&current, new_command);
	}
	return (new_node);
}
