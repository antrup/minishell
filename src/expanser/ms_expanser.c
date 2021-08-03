/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expanser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 09:41:43 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/03 13:55:49 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_exp_sqt(char *word, int *i, t_word **wlist)
{
	int			y;
	t_word		*new;

	new = ms_create_part(wlist);
	if (!new)
		return (errno);
	y = *i + 1;
	while (word[y] && ms_isquote(word[y]) != STRING_SQ)
		y++;
	if (!word[y])
		return (ERR_SQUT);
	new->part = ft_substr(word, *i + 1, y - *i - 1);
	*i = y + 1;
	return (0);
}

static int	ms_exp_oth(char *word, int *i, t_word **wlist, int type)
{
	int			y;
	t_word		*new;

	new = ms_create_part(wlist);
	if (!new)
		return (errno);
	y = *i;
	if (type == -1)
	{	
		while (word[y] && !ms_isquote(word[y]) && !ms_isvariable(&(word[y])))
			y++;
	}
	else
	{
		while (word[y] && ms_isquote(word[y]) != type 
				&& !ms_isvariable(&(word[y])))
			y++;
	}
	new->part = ft_substr(word, *i, y - *i);
	if (!new->part)
		return (errno);
	*i = y;
	return (0);
}

static int	ms_exp_dqt(char *word, int *i, t_word **wlist)
{
	int		ret;

	(*i)++;
	ret = 0;
	while (word[*i] && ms_isquote(word[*i]) != STRING_DQ)
	{	
		if (ms_isvariable(&word[*i]))
			ret = ms_exp_var(word, i, wlist);
		else
			ret = ms_exp_oth(word, i, wlist, STRING_DQ);
		if (ret != 0)
			return (ret);
	}
	if (!word[*i])
		return (ERR_DQUT);
	(*i)++;
	return (0);
}

static int	ms_expand_tk_value(t_tlist *token)
{	
	int		i;
	int		err;
	t_word	*wlist;

	i = 0;
	err = 0;
	wlist = NULL;
	while (token->tk.value[i] && !err)
	{
		if (ms_isquote(token->tk.value[i]) == STRING_SQ && !err)
			err = ms_exp_sqt(token->tk.value, &i, &wlist);
		else if (ms_isvariable(&(token->tk.value[i])) && !err)
			err = ms_exp_var(token->tk.value, &i, &wlist);
		else if (ms_isquote(token->tk.value[i]) == STRING_DQ && !err)
			err = ms_exp_dqt(token->tk.value, &i, &wlist);
		else if (!err)
			err = ms_exp_oth(token->tk.value, &i, &wlist, -1);
	}
	free(token->tk.value);
	token->tk.value = ms_concat(wlist, &err);
	if (wlist)
		ms_clean_wlist(wlist);
	if (err)
		return (1);
	return (0);
}

int	ms_expanser(t_tlist **tokens)
{
	t_tlist		*token;
	int			err;

	token = *tokens;
	err = 0;
	while (token && token->tk.type != OP_AND && token->tk.type != OP_OR)
	{
		if (token->tk.type == WORD || token->tk.type == VAR)
			err = ms_expand_tk_value(token);
		if (token->tk.type == VAR && !err)
			err = ms_var_tokens(token->tk.value, tokens, &token);
		if (err)
			return (1);
		token = token->next;
	}
	return (0);
}
