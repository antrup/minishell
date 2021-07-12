/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expanser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 09:41:43 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/12 11:39:15 by sshakya          ###   ########.fr       */
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
		return (0);
	new = ms_create_part(wlist);
	if (!new)
		return (1);
	new->part = malloc(sizeof(char) * (ft_strlen(getenv(var)) + 1));
	if (!new->part)
		return (1);
	ft_strlcpy(new->part, getenv(var), ft_strlen(getenv(var) + 1));
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
	while (word[y] && ms_isquote(word[y]) !=  STRING_SQ)
		y++;
	if (!word[y])
		return (1);
	new->part = ft_substr(word, *i + 1, y - *i - 1);
	*i = y + 1;
	return (0);
}

static int	ms_exp_oth(char *word, int *i, t_word **wlist)
{
	int			y;
	t_word		*new;

	new = ms_create_part(wlist);
		if (!new)
			return (1);
	y = *i;
	while (word[y] && !ms_isquote(word[y]) && !ms_isvariable(&(word[y])))
		y++;
	new->part = ft_substr(word, *i, y - *i);
	*i = y;
	return (0);
}

static int ms_exp_dqt(char *word, int *i, t_word **wlist)
{
	int		ret;

	(*i)++;
	ret = 0;
	while (word[*i] && ms_isquote(word[*i]) != STRING_DQ)
	{	
		if (ms_isvariable(&word[*i]))
			ret = ms_exp_var(word, i, wlist);
		else
			ret = ms_exp_oth(word, i, wlist);
		if (ret == 1)
			return (1);
	}
	if (!word[*i])
		return (1);
	(*i)++;
	return (0);
}

char	*ms_expanser(char *word, t_ms *data)
{
	t_word		*wlist;
	int			i;
	
	wlist = NULL;
	(void)data;
	i = 0;
	while (word[i])
	{
		if (ms_isquote(word[i]) == STRING_SQ)
			ms_exp_sqt(word, &i, &wlist);
		else if (ms_isvariable(&(word[i])))
			ms_exp_var(word, &i, &wlist);
		else if (ms_isquote(word[i]) == STRING_DQ)
			ms_exp_dqt(word, &i, &wlist);
		else
			ms_exp_oth(word, &i, &wlist);
	}
	return (ms_concat(wlist));
}
