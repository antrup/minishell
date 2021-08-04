/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:36:33 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/04 22:45:33 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_isvariable(char *str)
{
	if (str[0] == '$' && (ft_isalnum(str[1])))
		return (1);
	return (0);
}

int	ms_is_sp_variable(char *str)
{
	if (str[0] == '$' && str[1] == '?')
		return (1);
	return (0);
}

int	ms_isparen(char c)
{
	if (c == '(' || c == ')')
		return (1);
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
