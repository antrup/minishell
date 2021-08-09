/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 09:45:13 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/09 09:45:16 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_hasvar(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static int	ms_exp_other(char *word, int *i, t_word **wlist)
{
	int			y;
	t_word		*new;

	new = ms_create_part(wlist);
	if (!new)
		return (1);
	y = *i;
	while (word[y] && word[y] != '$')
		y++;
	new->part = ft_substr(word, *i, y - *i);
	*i = y;
	return (0);
}

char	*ms_heredoc_expand(char *line)
{
	int		i;
	t_word	*list;
	int		error;

	i = 0;
	error = 0;
	list = NULL;
	while (line[i])
	{
		if (line[i] == '$')
			ms_exp_var(line, &i, &list);
		else
			ms_exp_other(line, &i, &list);
	}
	free(line);
	line = ms_concat(list, &error);
	ms_clean_wlist(list);
	return (line);
}
