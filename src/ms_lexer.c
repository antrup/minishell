/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:49:05 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/08 10:05:43 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_ctoken_word(char *line, t_tlist **tlist, int *i)
{
	t_tlist		*new;
	int			y;

	new = ms_create_token(tlist);
	if (!new)
		return (1);
	new->tk.type = WORD;
	y = *i + 1;
	while (line[y] && !ms_isquote(line[y]) && !ms_isop_pipe(line[y])
			&& !ms_isop_and(line[y], line[y + 1]) && !ft_isspace(line[y]))
		y++;
	new->tk.value = ft_substr(line, *i, y - *i);
	*i = y;
	return (0);
}

static int	ms_ctoken_qt(char *line, t_tlist **tlist, int *i, int type)
{
	t_tlist		*new;
	int			y;

	new = ms_create_token(tlist);
	if (!new)
		return (1);
	new->tk.type = STRING_DQ;
	y = *i + 1;
	while (ms_isquote(line[y]) != type && line[y])
		y++;
	if (!line[y])
		return (1);
	new->tk.value = ft_substr(line, *i + 1, y - *i - 1);
	*i = y + 1;
	retur (0);
}

static int	ms_ctoken_and(t_tlist **tlist, int *i)
{
	t_tlist		*new;

	new = ms_create_token(tlist);
	if (!new)
		return (1);
	new->tk.type = OP_AND;
	*i = *i + 2;
	return (0);
}

static int	ms_ctoken_pipe(char *line, t_tlist **tlist, int *i)
{
	t_tlist		*new;

	new = ms_create_token(tlist);
	if (!new)
		return (1);
	if (ms_isop_pipe(line[*i]) == OP_PIPE 
			&& ms_isop_pipe(line[*i + 1]) == OP_PIPE)
	{	
		new->tk.type = OP_OR;
		*i = *i + 1;
	}
	else
		new->tk.type = OP_PIPE;
	*i = *i + 1;
	return (0);
}

static int	ms_ctoken_re(char *line, t_tlist **tlist, int *i)
{
	t_tlist		*new;

	new = ms_create_token(tlist);
	if (!new)
		return (1);
	if (ms_isredirection(line[*i]) == REDIR_IN
			&& ms_isredirection(line[*i + 1]) == REDIR_IN)
	{	
		new->tk.type = REDIR_IN_A;
		*i = *i + 1;
	}
	else if (ms_isredirection(line[*i]) == REDIR_OUT 
			&& ms_isredirection(line[*i + 1]) == REDIR_OUT)
	{	
		new->tk.type = REDIR_OUT_A;
		*i = *i + 1;
	}
	else
		new->tk.type = ms_isop_pipe(line[*i]);
	*i = *i + 1;
	return (0);
}

int	ms_lexer(char *line, t_tlist **tlist)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (ms_isquote(line[i]))
			ms_ctoken_qt(line, tlist, &i, ms_isquote(line[i]));
		else if (ms_isop_pipe(line[i]))
			ms_ctoken_pipe(line, tlist, &i);
		else if (ms_isredirection(line[i]))
			ms_ctoken_re(line, tlist, &i);
		else if (ms_isop_and(line[i], line[i + 1]))
			ms_ctoken_and(tlist, &i);
		else
			ms_ctoken_word(line, tlist, &i);
	}
	return (0);
}
