/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 00:17:37 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/27 02:27:45 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_newline(int sig)
{
	(void)sig;
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ms_exit(int sig)
{
	(void)sig;
	write(1, "exit\n", 5);
	tcsetattr(0, TCSANOW, &g_shell.data->info.term_ios);
	ms_clean(g_shell.data);
	g_shell.on = 0;
	rl_clear_history();
	exit (0);
}

void	ms_clean_tlist(t_tlist **list)
{
	t_tlist	*temp;

	while (*list && (*list)->tk.type != OP_AND && (*list)->tk.type != P_OPEN
		&& (*list)->tk.type != OP_OR)
	{
		temp = (*list)->next;
		if ((*list)->tk.value)
			free((*list)->tk.value);
		free(*list);
		*list = temp;
	}
	if (*list && (*list)->tk.type == OP_AND)
	{
		temp = (*list)->next;
		free(*list);
	}
	if (*list && (*list)->tk.type == OP_OR)
	{
		temp = (*list)->next;
		free(*list);
	}
	if (*list && (*list)->tk.type == P_OPEN)
	{
		temp = (*list)->next;
		free(*list);
	}
	*list = temp;
}

void	ms_clean_tk_all_or(t_tlist **list)
{
	t_tlist	*temp;

	while (*list && (*list)->tk.type != OP_AND && (*list)->tk.type != P_OPEN)
	{
		temp = (*list)->next;
		if ((*list)->tk.value)
			free((*list)->tk.value);
		free(*list);
		*list = temp;
	}
	if (*list && (*list)->tk.type == P_OPEN)
	{
		temp = (*list)->next;
		free(*list);
	}
	*list = temp;
}

void	ms_clean_cmd(t_node **node)
{
	int	i;

	i = 0;
	if (*node)
	{
		if ((*node)->type == NO_CMD)
		{
			free((*node)->data->cmd);
			free((*node)->data->delimiter);
			if ((*node)->data->args)
			{
				while ((*node)->data->args[i])
				{
					free((*node)->data->args[i]);
					i++;
				}
			}
			free((*node)->data->args);
			free((*node)->data);
		}
		if ((*node)->type == NO_PIPE)
		{
			ms_clean_cmd(&(*node)->right);
			ms_clean_cmd(&(*node)->left);
		}
		free(*node);
	}
}

void	ms_clean_wlist(t_word *list)
{
	t_word	*temp;

	while (list)
	{
		temp = list->next;
		free (list->part);
		free(list);
		list = temp;
	}
}

void	ms_clean(t_ms *data)
{
	if (data->tokens)
		ms_clean_tlist(&data->tokens);
	free(data->line);
}
