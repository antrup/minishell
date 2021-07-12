/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expanser_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:38:09 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/12 11:39:10 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int ms_isparen(char c)
{
	if (c == '(')
		return (1);
	if (c == ')')
		return (2);
	return (0);
}

int	ms_isvariable(char *str)
{
	if (str[0] == '$' && (ft_isalnum(str[1])))
		return (1);
	return (0);
}

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
	if (!current->next)
		return (wlist->part);
	else
	{
		str = current->part;
		flag = 0;
		while (current->next)
		{
			temp = ft_strjoin(str, current->next->part);
			if (flag)
				free(str);
			flag = 1;
			str = temp;
			current = current->next;
		}
	}
	return (str);
}

