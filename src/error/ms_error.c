/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 14:51:16 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/09 01:17:43 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

/*
** NEED SINGLE PROTOTYPE TO EXIT DURING LEXER/PARSER/OTHER !!!!!!!
*/
static void	ms_errmsg(int id, char *str)
{
	if (id == ERR_SYN)
		ft_putstr_fd(2, "syntax error near unexpected token");
	if (id == ERR_TK)
		ft_putstr_fd(2, "error message for ERR_TK");
	if (str)
		ft_putstr_fd(2, str);
}

void	ms_error_token(t_tlist *tlist, int id)
{
	(void)tlist;
	if (id == ERR_SYN)
		ms_errmsg(ERR_SYN, "'|'");
	return ;
}

void	ms_error(t_ms *data, int id)
{
	ms_clean(data);
	return ;
}
