/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expanser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 09:41:43 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/06 21:47:19 by atruphem         ###   ########.fr       */
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
		if (ms_isquote(token->tk.value[i]) == STRING_SQ)
			err = ms_exp_sqt(token->tk.value, &i, &wlist);
		else if (ms_isvariable(&(token->tk.value[i])))
			err = ms_exp_var(token->tk.value, &i, &wlist);
		else if (ms_isquote(token->tk.value[i]) == STRING_DQ)
			err = ms_exp_dqt(token->tk.value, &i, &wlist);
		else if (ms_is_sp_variable(&(token->tk.value[i])))
			err = ms_exp_spvar(&i, &wlist);
		else
			err = ms_exp_oth(token->tk.value, &i, &wlist, -1);
	}
	free(token->tk.value);
	token->tk.value = ms_concat(wlist, &err);
	if (wlist)
		ms_clean_wlist(wlist);
	return (err);
}

int	ms_expanser(t_tlist **tokens)
{
	t_tlist		*token;
	int			err;

	token = *tokens;
	err = 0;
	while (token && token->tk.type != OP_AND && token->tk.type != OP_OR)
	{
		if (token->tk.type == WORD || token->tk.type == OP_VAR)
			err = ms_expand_tk_value(token);
		if (token->tk.type == OP_VAR && !err)
			err = ms_var_tokens(token->tk.value, tokens, &token);
		if (token->tk.type == WORD && ms_iswildcard(token->tk.value))
			err = ms_wildcard(&token, tokens);
		if (err)
			return (1);
		token = token->next;
	}
	return (0);
}
