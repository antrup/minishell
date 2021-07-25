/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 00:17:37 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/25 16:49:37 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_exit(int sig)
{
	if (sig == SIGINT)
		write(1, "exit\n", 5);
	tcsetattr(0, TCSANOW, &g_shell.data->info.term_ios);
	ms_clean(g_shell.data);
	g_shell.on = 0;
	exit (0);
}

void	ms_clean_tlist(t_tlist **list)
{
	t_tlist *temp;

	while (*list)
	{
		temp = (*list)->next;
		if ((*list)->tk.value)
			free((*list)->tk.value);
		free(*list);
		*list = temp;
	}
}

void	ms_clean_cmd(t_node *head)
{
	int	i;
	i = 0;
	if (head)
	{
		if (head->type == NO_CMD)
		{
			free((head)->data->cmd);
			free((head)->data->delimiter);
			while ((head)->data->args && (head)->data->args[i])
			{
				free((head)->data->args[i]);
				i++;
			}
			free((head)->data->args);
			free((head)->data);
		}
		free(head);
	}
}

void	ms_clean_wlist(t_word *list)
{
	t_word *temp;

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
	//clear_history();
}
