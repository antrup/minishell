/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:49:05 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/08 13:01:49 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_lexer(char *line, t_tlist **tokens)
{
	int		i;
	int		err;

	i = 0;
	err = 0;
	while (line && line[i] && !err)
	{
		if (ft_isspace(line[i]))
			i++;
		else if (ms_isop_pipe(line[i]))
			err = ms_ctoken_pipe(line, tokens, &i);
		else if (ms_isredirection(line[i]) && !err)
			err = ms_ctoken_re(line, tokens, &i);
		else if (ms_isop_and(line[i], line[i + 1]) && !err)
			err = ms_ctoken_and(tokens, &i);
		else if (ms_isop_or(line[i], line[i + 1]) && !err)
			err = ms_ctoken_or(tokens, &i);
		else if (line[i] == '(')
			err = ms_ctoken_parenthesis(line, tokens, &i);
		else
			err = ms_ctoken_word(line, tokens, &i, 0);
	}
	return (err);
}
