/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clean_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 14:13:50 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/05 08:15:38 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_clean_tlist_cmd(t_tlist **list)
{
	t_tlist	*temp;

	while (*list && (*list)->tk.type != OP_AND && (*list)->tk.type != OP_OR)
	{
		temp = (*list)->next;
		if ((*list)->tk.value)
			free((*list)->tk.value);
		free(*list);
		*list = temp;
	}
	if (*list && ((*list)->tk.type == OP_AND || (*list)->tk.type == OP_OR))
	{
		temp = (*list)->next;
		free(*list);
		*list = temp;
		(*list)->previous = NULL;
	}
}

void	ms_clean_tlist_or(t_tlist **list)
{
	t_tlist	*temp;

	while (*list && (*list)->tk.type != OP_AND)
	{
		temp = (*list)->next;
		if ((*list)->tk.value)
			free((*list)->tk.value);
		free(*list);
		*list = temp;
	}
	if (*list && ((*list)->tk.type == OP_AND || (*list)->tk.type == OP_OR))
	{
		temp = (*list)->next;
		free(*list);
		*list = temp;
		(*list)->previous = NULL;
	}
}

int	ms_clean_tlist_all(t_tlist **list)
{
	t_tlist	*temp;

	while (*list)
	{
		temp = (*list)->next;
		if ((*list)->tk.value)
			free((*list)->tk.value);
		free(*list);
		*list = temp;
	}
	return (1);
}

int	ms_clean_tlist_parenthesis(t_tlist **list)
{
	t_tlist	*temp;

	if (*list && (*list)->tk.type == OP_PAREN)
	{
		temp = (*list)->next;
		if ((*list)->tk.value)
			free((*list)->tk.value);
		free(*list);
		*list = temp;
	}
	return (1);
}

void	ms_clean_tokens(t_tlist **tokens, t_markers op)
{
	if (*tokens && (*tokens)->tk.type == OP_PAREN)
		ms_clean_tlist_parenthesis(tokens);
	if (op._or > 0 && op.ret == 0)
		ms_clean_tlist_or(tokens);
	else if (op._and > 0 && g_shell.rvar != 0)
		ms_clean_tlist_all(tokens);
	else
		ms_clean_tlist_cmd(tokens);
}
