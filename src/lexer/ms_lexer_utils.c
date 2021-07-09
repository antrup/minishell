/* ************************************************************************** */
/*                 :                                                           */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:36:33 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/09 16:38:31 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_isredirection(char c)
{
	if (c == '<')
		return (REDIR_IN);
	if (c == '>')
		return (REDIR_OUT);
	return (0);
}

int	ms_isop_pipe(char c)
{
	if (c == '|')
		return (OP_PIPE);
	return (0);
}

int	ms_isop_and(char c, char b)
{
	if (c == '&' && b == '&')
		return (OP_AND);
	return (0);
}

int	ms_isquote(char c)
{
	if (c == '"')
		return (STRING_DQ);
	if (c == '\'')
		return (STRING_SQ);
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
