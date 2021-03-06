/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expanser_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:38:09 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/08 11:48:58 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

t_word	*ms_create_part(t_word **wlist)
{
	t_word		*new;
	t_word		*current;

	new = malloc(sizeof(t_word));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->part = NULL;
	current = wlist[0];
	if (!current)
		wlist[0] = new;
	else
	{	
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (new);
}

int	ms_exp_spvar(int *i, t_word **wlist)
{
	t_word	*new;

	*i = *i + 2;
	new = ms_create_part(wlist);
	new->part = ft_itoa(g_shell.rvar);
	return (0);
}

static int	ms_null_var(t_word *new, char *var)
{
	free(var);
	new->part = malloc(sizeof(char) * 1);
	if (!new->part)
		return (errno);
	ft_strlcpy(new->part, "", 1);
	return (0);
}

int	ms_exp_var(char *word, int *i, t_word **wlist)
{
	t_word	*new;
	int		y;
	char	*var;

	y = *i + 1;
	while (word[y] && ft_isalnum(word[y]))
		y++;
	var = ft_substr(word, *i + 1, y - *i - 1);
	*i = y;
	new = ms_create_part(wlist);
	if (!new)
		return (errno);
	if (getenv(var) == NULL)
		return (ms_null_var(new, var));
	new->part = malloc(sizeof(char) * (ft_strlen(getenv(var)) + 1));
	if (!new->part)
		return (errno);
	ft_strlcpy(new->part, getenv(var), ft_strlen(getenv(var)) + 1);
	free(var);
	return (0);
}
