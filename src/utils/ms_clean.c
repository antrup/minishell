/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 00:17:37 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/12 18:02:10 by sshakya          ###   ########.fr       */
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

void	ms_clean(t_ms *data)
{
	ms_clean_tlist(data->tlist);
	free(data->history);
	//clear_history();
}
