/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expanser_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:38:09 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/16 12:00:55 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

t_word	*ms_create_part(t_word **wlist)
{
	t_word		*new;
	t_word		*current;

	new = malloc(sizeof(t_word));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->part = NULL;
	current = wlist[0];
	if (!current)
		wlist[0] = new;
	else
	{	
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (new);
}

char	*ms_concat(t_word *wlist)
{
	char		*temp;
	char		*str;
	t_word		*current;
	int			flag;

	current = wlist;
	flag = 0;
	if (current == NULL)
		return (NULL);
	if (!current->next)
		return (ft_strdup(wlist->part));
	else
	{
		str = current->part;
		while (current->next)
		{
			temp = ft_strjoin(str, current->next->part);
			if (flag)
				free(str);
			str = temp;
			flag = 1;
			current = current->next;
		}
	}
	return (str);
}
