/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:49:05 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/07 21:28:10 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_ctoken_str(char *line, t_tlist **tlist, int *i)
{
	t_tlist		*new;
	int			y;

	new = ms_create_token(tlist);
	if (!new)
		return (1);
	new->tk.type = STRING;
	y = *i + 1;
	while (line[y] && !ms_isquote(line[y]) && !ms_isop_pipe(line[y])
			&& !ms_isop_and(line[y], line[y + 1]) && !ms_isvariable(&line[y]))
		y++;
	new->tk.value = ft_substr(line, *i, y - *i);
	*i = y;
	return (0);
}

static int	ms_ctoken_var(char *line, int *i, t_tlist **tlist)
{
	t_tlist	*new;
	int		y;
	int		paren;

	new = ms_create_token(tlist);
	if (!new)
		return(1);
	new->tk.type = VARIABLE;
	y = *i + 1;
	paren = ms_isparen(line[y]);
	if (paren == 1)
	{
		y++;
		while (line[y] && paren)
		{
			if (ms_isparen(line[y] == 1))
				paren += 1;
			if (ms_isparen(line[y]) == 2)
				paren -= 1;
			y++;
		}
	}
	else 
	{
		while (line[y] && !ft_isspace(line[y]))
			y++;
	}
	if (!line[y])
		return (1);
	new->tk.value = ft_substr(line, *i + 1, y - *i);
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
	new->tk.value = ft_substr(line, *i + 1, y - 1);
	*i = y + 1;
	return (0);
}

static int	ms_ctoken_and(t_tlist **tlist, int *i)
{
	t_tlist		*new;

	new = ms_create_token(tlist);
	if (!new)
		return (1);
	new->tk.type = OPERATOR;
	new->tk.op = OP_AND;
	*i = *i + 2;
	return (0);
}

static int	ms_ctoken_pipe(char *line, t_tlist **tlist, int *i)
{
	t_tlist		*new;

	new = ms_create_token(tlist);
	if (!new)
		return (1);
	new->tk.type = OPERATOR;
	if (ms_isop_pipe(line[*i]) == OP_PIPE 
			&& ms_isop_pipe(line[*i + 1]) == OP_PIPE)
	{	
		new->tk.op = OP_OR;
		*i = *i + 1;
	}
	else
		new->tk.op = OP_PIPE;
	*i = *i + 1;
	return (0);
}

static int	ms_ctoken_re(char *line, t_tlist **tlist, int *i)
{
	t_tlist		*new;

	new = ms_create_token(tlist);
	if (!new)
		return (1);
	new->tk.type = REDIRECTION;
	if (ms_isredirection(line[*i]) == REDIR_IN
			&& ms_isredirection(line[*i + 1]) == REDIR_IN)
	{	
		new->tk.op = REDIR_IN_A;
		*i = *i + 1;
	}
	else if (ms_isredirection(line[*i]) == REDIR_OUT 
			&& ms_isredirection(line[*i + 1]) == REDIR_OUT)
	{	
		new->tk.op = REDIR_OUT_A;
		*i = *i + 1;
	}
	else
		new->tk.op = ms_isop_pipe(line[*i]);
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
		else if (ms_isvariable(&(line[i])))
			ms_ctoken_var(line, &i, tlist);
		else
			ms_ctoken_str(line, tlist, &i);
	}
	return (0);
}
