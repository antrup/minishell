/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ctoken_op2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 14:18:57 by toni              #+#    #+#             */
/*   Updated: 2021/08/08 14:19:23 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_ctoken_and(t_tlist **tokens, int *i)
{
	t_tlist		*new;

	new = ms_create_token(tokens);
	if (!new)
		return (errno);
	new->tk.type = OP_AND;
	*i = *i + 2;
	return (0);
}

int	ms_ctoken_or(t_tlist **tokens, int *i)
{
	t_tlist		*new;

	new = ms_create_token(tokens);
	if (!new)
		return (errno);
	new->tk.type = OP_OR;
	*i = *i + 2;
	return (0);
}
