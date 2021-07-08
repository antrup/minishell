/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 14:51:16 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/08 19:13:56 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_error_token(t_tlist *tlist, int errnum)
{
	(void)errnum;
	(void)tlist;
}

void	ms_error(t_ms *data, int type)
{
	if (data->tlist)
		ms_clean(data);
	return ;
}
