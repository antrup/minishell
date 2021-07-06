/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mn_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:14:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/06 20:02:41 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_init(t_ms *data)
{
	ft_memset(data, 0, sizeof(t_ms));
	data->tlist = NULL;
}

void	ms_clean(t_ms *data)
{
	t_tlist *temp;
	t_tlist *head;

	head = data->tlist;
	while (head)
	{
		temp = data->tlist->next;
		free(head->tk.value);
		free(head);
		head = temp;
	}
}

int		is_interactive(void)
{
	int	ret;

	ret = isatty(0);
	return (ret);
}
