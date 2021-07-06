/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:49:05 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/06 19:51:20 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int ms_isoperator(char c)
{
	if (c == '<')
		return (1);
	if (c == '>')
		return (2);
	if (c == '|')
		return (3);
	if (c == '&')
		return (4);
	return (0);
}
// || -> 5
// && -> 6
static int ms_isquote(char c)
{
	if (c == '"')
		return (1);
	if (c == '\'')
		return (2);
	return (0);
}

static int ms_ctoken_str(char *line, t_tlist **tlist, int *i)
{
	t_tlist		*new;
	t_tlist		*current;
	int			y;

	new = malloc(sizeof(t_tlist));
	if (!new)
		return (1);
	current = tlist[0];
	if (!current)
		tlist[0] = new;
	else
	{	
		while (current->next)
			current = current->next;
		current->next = new;
	}
	new->next = NULL;
	new->tk.type = STRING;
	y = *i + 1;
	while (!ms_isquote(line[y]) && !ms_isoperator(line[y]) && line[y])
		y++;
	new->tk.value = ft_substr(line, *i, y - *i);
	*i = y;
	return (0);
}

static int ms_ctoken_qt(char *line, t_tlist **tlist, int *i, int type)
{
	t_tlist		*new;
	t_tlist		*current;
	int			y;

	new = malloc(sizeof(t_tlist));
	if (!new)
		return (1);
	current = tlist[0];
	if (!current)
		tlist[0] = new;
	else
	{	
		while (current->next)
			current = current->next;
		current->next = new;
	}
	new->next = NULL;
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

static int ms_ctoken_op(char *line, t_tlist **tlist, int *i)
{
	t_tlist		*new;
	t_tlist		*current;

	new = malloc(sizeof(t_tlist));
	if (!new)
		return (1);
	current = tlist[0];
	if (!current)
		tlist[0] = new;
	else
	{	
		while (current->next)
			current = current->next;
		current->next = new;
	}
	new->next = NULL;
	new->tk.type = OPERATOR;
	if (ms_isoperator(line[*i]) == 3 && ms_isoperator(line[*i + 1]) == 3)
	{	
		new->tk.op = 5;
		*i = *i + 1;
	}
	else if (ms_isoperator(line[*i]) == 4 && ms_isoperator(line[*i + 1]) == 4)
	{	
		new->tk.op = 6;
		*i = *i + 1;
	}
	else
		new->tk.op = ms_isoperator(line[*i]);
	*i = *i + 1;
	return (0);
}

int	ms_lexer(char *line, t_tlist **tlist)
{
	int		i;

	i = 0;
	while(line[i])
	{
		if (ms_isquote(line[i]))
			ms_ctoken_qt(line, tlist, &i, ms_isquote(line[i]));
		else if (ms_isoperator(line[i]))
			ms_ctoken_op(line, tlist, &i);
		else
			ms_ctoken_str(line, tlist, &i);
		printf("%d\n", i);
	}
	return (0);
}
