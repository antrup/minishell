/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcard_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 11:09:01 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/08 11:20:31 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

t_tlist	*ms_iswild(t_tlist **head)
{
	t_tlist	*iswild;

	iswild = *head;
	while (iswild)
	{
		if (iswild->tk.type == WORD && ms_iswildcard(iswild->tk.value))
			return (iswild);
		iswild = iswild->next;
	}
	return (NULL);
}

t_tlist	*ms_insert_matches(t_tlist **head, t_tlist *matches, t_tlist *iswild)
{
	t_tlist	*next;

	next = NULL;
	if (iswild->previous)
	{
		iswild->previous->next = matches;
		matches->previous = iswild->previous;
	}
	else
		*head = matches;
	if (iswild)
		next = iswild->next;
	if (next)
		next->previous = matches;
	return (next);
}

int	ms_ctoken_matches(t_tlist **wtoken, t_wcard *files)
{
	t_tlist	*buff;

	while (files)
	{
		if (files->ismatch == 1)
		{
			buff = ms_create_token(wtoken);
			if (buff == NULL)
				return (errno);
			buff->tk.value = ft_strdup(files->str);
			if (buff->tk.value == NULL)
				return (errno);
			buff->tk.type = WORD;
		}
		files = files->next;
	}
	return (0);
}

static int	ms_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s2[i] != '\0' && s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

void	ms_sort_files(t_wcard *file)
{
	int		i;
	char	*temp;
	int		is_sorted;

	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		i = 0;
		while (file->next != NULL)
		{
			if (ms_strcmp(file->str, file->next->str) > 0)
			{
				temp = file->str;
				file->str = file->next->str;
				file->next->str = temp;
				is_sorted = 0;
			}
			file = file->next;
		}
	}
}
