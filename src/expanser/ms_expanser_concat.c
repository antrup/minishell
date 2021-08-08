/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expanser_concat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 11:48:30 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/08 11:48:51 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static char	*ms_join_wlist(t_word *current, int *error)
{
	char	*str;
	char	*temp;
	int		flag;

	flag = 0;
	str = current->part;
	while (current->next)
	{
		temp = ft_strjoin(str, current->next->part);
		if (!temp)
		{
			*error = errno;
			return (NULL);
		}
		if (flag)
			free(str);
		str = temp;
		flag = 1;
		current = current->next;
	}
	return (str);
}

char	*ms_concat(t_word *wlist, int *error)
{
	char		*str;
	t_word		*current;

	current = wlist;
	if (current == NULL)
		return (ft_strdup(""));
	if (!current->next)
	{
		str = ft_strdup(wlist->part);
		if (!str && wlist->part != NULL)
			*error = errno;
		return (str);
	}
	else
		str = ms_join_wlist(current, error);
	return (str);
}
