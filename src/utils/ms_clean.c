/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 00:17:37 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/24 10:53:58 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_exit(int sig)
{
	if (sig == SIGINT)
		write(1, "exit\n", 5);
	if (sig == SIGQUIT)
		write(1, "exit\n", 5);
	if (sig == SIGTERM)
		printf("test\n");
	exit(0);
}

static void	ms_clean_tlist(t_tlist *list)
{
	t_tlist *temp;

	while (list)
	{
		temp = list->next;
		if (list->tk.value)
			free(list->tk.value);
		free(list);
		list = temp;
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
	ms_clean_tlist(data->tokens);
	free(data->line);
	//clear_history();
}
