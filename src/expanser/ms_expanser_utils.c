/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expanser_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:38:09 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/05 04:33:08 by sshakya          ###   ########.fr       */
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

int	ms_exp_var(char *word, int *i, t_word **wlist)
{
	t_word	*new;
	int		y;
	char	*var;

	y = *i + 1;
	while (word[y] && ft_isalnum(word[y]))
		y++;
	var = ft_substr(word, *i + 1, y - *i - 1);
	*i = y;
	if (getenv(var) == NULL)
	{
		free(var);
		return (0);
	}
	new = ms_create_part(wlist);
	if (!new)
		return (errno);
	new->part = malloc(sizeof(char) * (ft_strlen(getenv(var)) + 1));
	if (!new->part)
		return (errno);
	ft_strlcpy(new->part, getenv(var), ft_strlen(getenv(var)) + 1);
	free(var);
	return (0);
}

char	*ms_concat(t_word *wlist, int *error)
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
	{
		str = ft_strdup(wlist->part);
		if (!str && wlist->part != NULL)
			*error = errno;
		return (str);
	}
	else
	{
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
	}
	return (str);
}
