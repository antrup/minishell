/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:36:33 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/04 22:45:28 by sshakya          ###   ########.fr       */
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

int	ms_isop_or(char c, char b)
{
	if (c == '|' && b == '|')
		return (OP_OR);
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
