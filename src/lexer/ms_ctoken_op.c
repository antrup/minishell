/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ctoken_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:38:52 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/08 14:22:58 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_check_parenthesis(char *line)
{
	int	len;

	if (!line || line[0] == '\0')
		return (1);
	len = ft_strlen(line);
	if (line[0] == '(' && line[len - 1] == ')')
		return (1);
	return (0);
}

static int	ms_set_parentoken(char *line, int *i, t_tlist *new, int n)
{
	new->tk.value = ft_substr(line, *i + 1, n - *i - 1);
	if (ms_check_parenthesis(new->tk.value))
	{
		ms_errmsg(ERR_SYN, new->tk.value);
		return (ERR_SYN);
	}
	*i = n + 1;
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
	new->tk.type = OP_PAREN;
	while (line[n])
	{	
		if (line[n] == '(')
			_open++;
		if (line[n] == ')')
			_open--;
		if (_open == -1)
			return (ms_set_parentoken(line, i, new, n));
		n++;
	}
	return (ms_errmsg_paren(ERR_SYN));
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
