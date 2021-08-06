/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 00:17:37 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/06 07:24:31 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_clean_environ(void)
{
	int	i;

	i = 0;
	if (g_shell.env_pt)
	{
		while (g_shell.env_pt[i])
		{	
			free(g_shell.env_pt[i]);
			i++;
		}
		free(g_shell.env_pt);
	}
	free(environ);
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
		ms_clean_tlist_all(&data->tokens, 0);
	if (data->thead)
		ms_clean_cmd(&data->thead);
	if (data->line)
		free(data->line);
	ms_clean_environ();
}
