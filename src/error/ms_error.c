/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 14:51:16 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/08 13:13:52 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_errmsg(int id, char *str)
{
	if (id == ERR_SYN)
		ft_putstr_fd("syntax error near unexpected token", 2);
	if (id == ERR_DQUT)
		ft_putstr_fd("unmatched - ' \" ' \n", 2);
	if (id == ERR_SQUT)
		ft_putstr_fd("unmatched - ' ' ' \n", 2);
	if (id == ERR_PAREN)
		ft_putstr_fd("missing - ' ) ' \n", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
}

static char	*ms_error_word(t_token *token)
{
	char	*errstr;
	char	*temp;

	temp = ft_strjoin(" `", token->value);
	errstr = ft_strjoin(temp, "'");
	free (temp);
	return (errstr);
}

static void	ms_error_token2(t_token *token)
{
	if (token->type == REDIR_IN_A)
		ms_errmsg(ERR_SYN, " `<<'");
	if (token->type == REDIR_OUT_A)
		ms_errmsg(ERR_SYN, " `>>'");
	if (token->type == OP_PAREN)
		ms_errmsg(ERR_SYN, " `('");
	return ;
}

void	ms_error_token(t_token *token)
{
	char	*str;

	str = NULL;
	if (token->type == WORD)
	{
		str = ms_error_word(token);
		ms_errmsg(ERR_SYN, str);
		free (str);
	}
	if (token->type == OP_PIPE)
		ms_errmsg(ERR_SYN, " `|'");
	if (token->type == OP_AND)
		ms_errmsg(ERR_SYN, " `&&'");
	if (token->type == OP_OR)
		ms_errmsg(ERR_SYN, " `||'");
	if (token->type == REDIR_IN)
		ms_errmsg(ERR_SYN, " `<'");
	if (token->type == REDIR_OUT)
		ms_errmsg(ERR_SYN, " `>'");
	ms_error_token2(token);
	return ;
}

void	ms_error(t_ms *data, int id)
{
	ms_clean(data);
	(void)id;
	return ;
}
