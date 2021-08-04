/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_markers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 04:00:17 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/04 04:00:47 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_markers(t_tlist *tokens, t_markers *op)
{
	while (tokens)
	{
		if (tokens->tk.type == OP_OR)
			op->_or += 1;
		if (tokens->tk.type == OP_AND)
			op->_and += 1;
		if (tokens->tk.type == P_OPEN)
			op->opn += 1;
		if (tokens->tk.type == P_CLOSE)
			op->cls += 1;
		tokens = tokens->next;
	}
}
