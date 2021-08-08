/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_syntax_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 12:52:10 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/08 13:06:56 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_check_first_tk(t_tlist *current)
{
	if (current->tk.type != WORD && current->tk.type != REDIR_IN
		&& current->tk.type != REDIR_OUT && current->tk.type != REDIR_IN_A
		&& current->tk.type != REDIR_OUT_A && current->tk.type != OP_VAR
		&& current->tk.type != OP_PAREN)
		return (1);
	return (0);
}
