/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:36:33 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/04 18:38:34 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_tk_quote(int y, int type, char *line)
{
	y++;
	while (line[y] && ms_isquote(line[y]) != type)
		y++;
	if (!line[y] && type == STRING_DQ)
	{
		ms_errmsg(ERR_DQUT, NULL);
		return (-1);
	}
	if (!line[y] && type == STRING_SQ)
	{	
		ms_errmsg(ERR_SQUT, NULL);
		return (-1);
	}
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
	if (ms_is_sp_variable(&line[*i]))
	{
		new->tk.type = VAR;
		new->tk.value = ft_substr(line, *i, 2);
		*i = *i + 2;
		return (0);
	}
	y = *i;
	while (line[y] && !ms_isop_pipe(line[y])
		&& !ms_isop_and(line[y], line[y + 1]) && !ft_isspace(line[y]))
	{	
		type = ms_isquote(line[y]);
		if (type)
		{	
			y = ms_tk_quote(y, type, line);
			if (y == -1)
				return (1);
		}
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
