/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 14:41:40 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/02 18:31:10 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_check_redir(t_tlist *current)
{
	if (current->tk.type == REDIR_IN || current->tk.type == REDIR_OUT 
		|| current->tk.type == REDIR_IN_A 
		|| current->tk.type == REDIR_OUT_A)
	{
		if (!current->next)
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			return (1);
		}
		if (current->next->tk.type != WORD && current->next->tk.type != VAR) 
		{
			ms_error_token(&(current->next->tk));
			return (1);
		}
	}
	return (0);
}

int	ms_check_op(t_tlist *current)
{
	if (current->tk.type == OP_PIPE || current->tk.type == OP_AND
		|| current->tk.type == OP_OR)
	{
		if (!current->next)
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			return (1);
		}
		if (current->next->tk.type != WORD 
			&& current->next->tk.type != REDIR_IN
			&& current->next->tk.type != REDIR_OUT 
			&& current->next->tk.type != REDIR_IN_A
			&& current->next->tk.type != REDIR_OUT_A
			&& current->next->tk.type != VAR)
		{
			ms_error_token(&(current->next->tk));
			return (1);
		}
	}
	return (0);
}

int	ms_check_syntax(t_tlist *tokens)
{
	t_tlist *current;
	
	current = tokens;
	if (current == NULL)
		return (1);
	if (current->tk.type != WORD && current->tk.type != REDIR_IN
		&& current->tk.type != REDIR_OUT && current->tk.type != REDIR_IN_A
		&& current->tk.type != REDIR_OUT_A && current->tk.typ != VAR)
	{
		ms_error_token(&(current->tk));
		return (1);
	}
	while (current)
	{
		if (ms_check_redir(current))
			return (1);
		if (ms_check_op(current))
			return (1);
		current = current->next;
	}
	return (0);
}


