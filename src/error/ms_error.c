/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 14:51:16 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/09 17:11:13 by sshakya          ###   ########.fr       */
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

static char	*ms_error_word(t_token token)
{
	char *errstr;
	char *temp;

	temp = ft_strjoin("'", token.value);
	errstr = ft_strjoin(temp, "'");
	free (temp);
	return (errstr);
}

void	ms_error_token(t_token token)
{
	char	*str;

	str = NULL;
	if (token.type == WORD)
	{
		str = ms_error_word(token);
		ms_errmsg(ERR_SYN, str);
		free (str);
	}
	if (token.type == OP_PIPE)
		ms_errmsg(ERR_SYN, "'|'\n");
	if (token.type == OP_AND)
		ms_errmsg(ERR_SYN, "'&&'\n");
	if (token.type == OP_OR)
		ms_errmsg(ERR_SYN, "'||'\n");
	if (token.type == REDIR_IN)
		ms_errmsg(ERR_SYN, "'<'\n");
	if (token.type == REDIR_OUT)
		ms_errmsg(ERR_SYN, "'>'\n");
	if (token.type == REDIR_IN_A)
		ms_errmsg(ERR_SYN, "'<<'\n");
	if (token.type == REDIR_OUT_A)
		ms_errmsg(ERR_SYN, "'>>'\n");
	return ;
}

void	ms_error(t_ms *data, int id)
{
	ms_clean(data);
	return ;
}