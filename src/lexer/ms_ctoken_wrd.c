/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ctoken_wrd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:43:21 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/08 12:16:23 by toni             ###   ########.fr       */
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
		new->tk.type = OP_VAR;
	y = *i;
	while (line[y] && !ms_isop_pipe(line[y])
		&& !ms_isop_and(line[y], line[y + 1]) && !ft_isspace(line[y]))
	{	
		type = ms_isquote(line[y]);
		if (type)
		{	
			y = ms_tk_quote(y, type, line);
			if (y == -1)
				return (ERR_SYN);
		}
		y++;
	}
	new->tk.value = ft_substr(line, *i, y - *i);
	*i = y;
	return (0);
}
