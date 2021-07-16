/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:36:33 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/16 09:49:12 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_tk_quote(int y, int type, char *line)
{
	y++;
	while (line[y] && ms_isquote(line[y]) != type)
		y++;
	if (!line[y] && type == STRING_DQ)
		return (ERR_DQUT);
	if (!line[y] && type == STRING_SQ)
		return (ERR_SQUT);
	return (y);
}

int	ms_ctoken_word(char *line, t_tlist **tlist, int *i)
{
	t_tlist		*new;
	int			y;
	int			type;

	new = ms_create_token(tlist);
	if (!new)
		return (errno);
	new->tk.type = WORD;
	if (ms_isvariable(&line[*i]))
		new->tk.type = VAR;
	y = *i;
	while (line[y] && !ms_isop_pipe(line[y])
		&& !ms_isop_and(line[y], line[y + 1]) && !ft_isspace(line[y]))
	{	
		type = ms_isquote(line[y]);
		if (type)
			y = ms_tk_quote(y, type, line);
		y++;
	}
	new->tk.value = ft_substr(line, *i, y - *i);
	*i = y;
	return (0);
}

t_tlist	*ms_create_token(t_tlist **tlist)
{
	t_tlist		*new;
	t_tlist		*current;

	new = malloc(sizeof(t_tlist));
	if (!new)
		return (NULL);
	new->tk.value = NULL;
	new->tk.type = ERROR;
	current = tlist[0];
	if (!current)
	{	
		tlist[0] = new;
		new->previous = NULL;
	}
	else
	{	
		while (current->next)
			current = current->next;
		current->next = new;
		new->previous = current;
	}
	new->next = NULL;
	return (new);
}
