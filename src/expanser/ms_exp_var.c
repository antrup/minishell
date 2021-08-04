/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exp_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 02:16:27 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/04 22:47:32 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static void	ms_add_token(t_tlist *vtoken, t_tlist **token)
{
	t_tlist	*isvar;
	t_tlist	*temp;
	t_tlist	*next;

	temp = *token;
	next = NULL;
	while (temp && temp->tk.type != VAR)
		temp = temp->next;
	isvar = temp;
	if (isvar->previous)
	{
		isvar->previous->next = vtoken;
		vtoken->previous = isvar->previous;
	}
	else
		*token = vtoken;
	if (isvar)
		next = isvar->next;
	if (next)
		next->previous = vtoken;
	while (vtoken->next)
		vtoken = vtoken->next;
	vtoken->next = next;
	free(isvar->tk.value);
	free(isvar);
}

static int	ms_clear_var(t_tlist **tokens)
{
	t_tlist	*temp;
	t_tlist	*next;
	t_tlist	*prev;

	temp = *tokens;
	while (temp)
	{
		if (temp->tk.type == VAR && temp->tk.value == NULL)
		{
			next = temp->next;
			prev = temp->previous;
			free(temp);
			temp = next;
			prev->next = next;
		}
		if (temp)
			temp = temp->next;
	}
	return (1);
}

int	ms_var_tokens(char *var, t_tlist **tokens, t_tlist **current)
{
	int		i;
	int		err;
	t_tlist	*vtoken;

	i = 0;
	err = 0;
	vtoken = NULL;
	if (var == NULL)
		return (ms_clear_var(tokens));
	while (var[i] && !err)
	{
		if (ft_isspace(var[i]))
			i++;
		else if (ms_isop_pipe(var[i]))
			err = ms_ctoken_pipe(var, &vtoken, &i);
		else if (ms_isredirection(var[i]))
			err = ms_ctoken_re(var, &vtoken, &i);
		else if (ms_isop_and(var[i], var[i + 1]))
			err = ms_ctoken_and(&vtoken, &i);
		else if (!err)
			err = ms_ctoken_word(var, &vtoken, &i);
	}
	if (err)
		return (ms_clean_tlist_all(&vtoken));
	ms_add_token(vtoken, tokens);
	*current = vtoken;
	return (0);
}
