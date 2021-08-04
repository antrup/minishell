/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:49:05 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/04 18:37:32 by sshakya          ###   ########.fr       */
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

int	ms_ctoken_parenthesis(char *line, t_tlist **tokens, int *i)
{
	t_tlist		*new;
	int			_open;
	int			n;

	_open = 0;
	n = *i + 1;
	new = ms_create_token(tokens);
	if (!new)
		return (errno);
	new->tk.type = P_OPEN;
	while (line[n])
	{	
		if (line[n] == '(')
			_open++;
		if (line[n] == ')')
			_open--;
		if (_open == -1)
		{
			new->tk.value = ft_substr(line, *i + 1, n - *i - 1);
			*i = n + 1;
			return (0);
		}
		n++;
	}
	return (0);
}

int	ms_ctoken_pipe(char *line, t_tlist **tokens, int *i)
{
	t_tlist		*new;

	new = ms_create_token(tokens);
	if (!new)
		return (errno);
	if (ms_isop_pipe(line[*i]) == OP_PIPE
		&& ms_isop_pipe(line[*i + 1]) == OP_PIPE)
	{	
		new->tk.type = OP_OR;
		*i = *i + 1;
	}
	else
		new->tk.type = OP_PIPE;
	*i = *i + 1;
	return (0);
}

int	ms_ctoken_re(char *line, t_tlist **tokens, int *i)
{
	t_tlist		*new;

	new = ms_create_token(tokens);
	if (!new)
		return (errno);
	if (ms_isredirection(line[*i]) == REDIR_IN
		&& ms_isredirection(line[*i + 1]) == REDIR_IN)
	{	
		new->tk.type = REDIR_IN_A;
		*i = *i + 1;
	}
	else if (ms_isredirection(line[*i]) == REDIR_OUT
		&& ms_isredirection(line[*i + 1]) == REDIR_OUT)
	{	
		new->tk.type = REDIR_OUT_A;
		*i = *i + 1;
	}
	else
		new->tk.type = ms_isredirection(line[*i]);
	*i = *i + 1;
	return (0);
}

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
			err = ms_ctoken_word(line, tokens, &i);
	}
	return (err);
}
