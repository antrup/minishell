/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expanser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 09:41:43 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/08 09:53:58 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ms_minishell.h"

static int	ms_ctoken_var(char *line, int *i, t_tlist **tlist)
{
	t_tlist	*new;
	int		y;
	int		paren;

	new = ms_create_token(tlist);
	if (!new)
		return(1);
	new->tk.type = VARIABLE;
	y = *i + 1;
	paren = ms_isparen(line[y]);
	if (paren == 1)
	{
		y++;
		while (line[y] && paren)
		{
			if (ms_isparen(line[y] == 1))
				paren += 1;
			if (ms_isparen(line[y]) == 2)
				paren -= 1;
			y++;
		}
	}
	else 
	{
		while (line[y] && !ft_isspace(line[y]))
			y++;
	}
	if (!line[y])
		return (1);
	new->tk.value = ft_substr(line, *i + 1, y - *i);
	*i = y;
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