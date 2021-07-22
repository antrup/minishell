/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 00:17:37 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/23 01:15:16 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

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
	tcsetattr(0, TCSANOW, &data->info.term_ios);
	free(data->line);
	//clear_history();
}
