/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expanser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 09:41:43 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/23 15:45:27 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_exp_var(char *word, int *i, t_word **wlist)
{
	t_word	*new;
	int		y;
	char	*var;

	y = *i + 1;
	while (word[y] && ft_isalnum(word[y]))
		y++;
	var = ft_substr(word, *i + 1, y - *i - 1);
	*i = y;
	if (getenv(var) == NULL)
	{
		free(var);
		return (0);
	}
	new = ms_create_part(wlist);
	if (!new)
		return (1);
	new->part = malloc(sizeof(char) * (ft_strlen(getenv(var)) + 1));
	if (!new->part)
		return (1);
	ft_strlcpy(new->part, getenv(var), ft_strlen(getenv(var)) + 1);
	free(var);
	return (0);
}

static int	ms_exp_sqt(char *word, int *i, t_word **wlist)
{
	int			y;
	t_word		*new;

	new = ms_create_part(wlist);
	if (!new)
		return (1);
	y = *i + 1;
	while (word[y] && ms_isquote(word[y]) != STRING_SQ)
		y++;
	if (!word[y])
		return (1);
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
		return (1);
	y = *i;
	while (word[y] && ms_isquote(word[y]) != type && !ms_isvariable(&(word[y])))
		y++;
	new->part = ft_substr(word, *i, y - *i);
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
		if (ret == 1)
			return (1);
	}
	if (!word[*i])
		return (1);
	(*i)++;
	return (0);
}

void	ms_expanser(t_tlist *tokens)
{
	t_word		*wlist;
	t_tlist		*token;
	int			i;

	token = tokens;
	while (token)
	{
		wlist = NULL;
		if (token->tk.type == WORD || token->tk.type == VAR)
		{
			i = 0;
			while (token->tk.value[i])
			{
				if (ms_isquote(token->tk.value[i]) == STRING_SQ)
					ms_exp_sqt(token->tk.value, &i, &wlist);
				else if (ms_isvariable(&(token->tk.value[i])))
					ms_exp_var(token->tk.value, &i, &wlist);
				else if (ms_isquote(token->tk.value[i]) == STRING_DQ)
					ms_exp_dqt(token->tk.value, &i, &wlist);
				else
					ms_exp_oth(token->tk.value, &i, &wlist, -1);
			}
			free(token->tk.value);
			token->tk.value = ms_concat(wlist);
			if (wlist)
				ms_clean_wlist(wlist);
		}
		if (token->tk.type == VAR)
			ms_var_tokens(token->tk.value, &tokens);
		token = token->next;
	}
}
