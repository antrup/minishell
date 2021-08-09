/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 14:51:16 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/09 10:34:28 by sshakya          ###   ########.fr       */
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
	if (id == ERR_EMPTY_PAREN)
		ft_putstr_fd("syntax error in expression", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
}

static void	ms_error_word(t_token *token)
{
	char	*errstr;
	char	*temp;

	temp = ft_strjoin(" `", token->value);
	errstr = ft_strjoin(temp, "'");
	free (temp);
	ms_errmsg(ERR_SYN, errstr);
	free(errstr);
}

void	ms_error_token(t_token *token)
{
	char	*str;

	str = NULL;
	if (token->type == WORD)
		ms_error_word(token);
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
	if (token->type == REDIR_IN_A)
		ms_errmsg(ERR_SYN, " `<<'");
	if (token->type == REDIR_OUT_A)
		ms_errmsg(ERR_SYN, " `>>'");
	if (token->type == OP_PAREN)
		ms_errmsg(ERR_SYN, " `('");
	return ;
}

int	ms_errmsg_paren(int ret)
{
	ft_putstr_fd("missing - ' ) ' \n", 2);
	return (ret);
}

void	ms_error(t_ms *data, int id)
{
	ms_clean(data);
	(void)id;
	return ;
}
