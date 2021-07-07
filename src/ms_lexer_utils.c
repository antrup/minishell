/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:36:33 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/07 20:46:03 by sshakya          ###   ########.fr       */
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

int ms_isparen(char c)
{
	if (c == '(')
		return (1);
	if (c == ')')
		return (2);
	return (0);
}

int	ms_isvariable(char *str)
{
	if (str[0] == '$' && (ft_isalnum(str[1]) || ms_isparen(str[1]) == 1))
		return (1);
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
		return (1);
	if (c == '\'')
		return (2);
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
	new->tk.op = -1;
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
	return (new);
}
