/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 04:14:29 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/08 11:16:54 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static char	*ms_part(char *line, int *i, int count)
{
	int		n;
	int		x;
	int		start;
	char	*ret;

	x = 0;
	n = 0;
	start = 0;
	ret = NULL;
	while (line[x])
	{
		if (line[x] == '*')
			n++;
		if (count && line[x] == '*' && n == count)
			start = x + 1;
		if (line[x] == '*' && n > count)
		{
			*i = x;
			return (ft_substr(line, start, x - start));
		}
		x++;
	}
	*i = x;
	return (ft_substr(line, start, x - start));
}

int	ms_create_sterm(t_wcard **head, char *line, int *i, int count)
{
	t_wcard	*new;
	t_wcard	*temp;

	temp = *head;
	new = malloc(sizeof(t_wcard));
	if (!new)
		return (errno);
	new->type = OP_STERM;
	new->ismatch = 0;
	new->str = ms_part(line, i, count);
	new->next = NULL;
	new->prev = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	return (0);
}

int	ms_create_wcard(t_wcard **head, int *i, int *count)
{
	t_wcard	*new;
	t_wcard	*temp;

	temp = *head;
	new = malloc(sizeof(t_wcard));
	if (!new)
		return (errno);
	*count += 1;
	*i += 1;
	new->type = OP_WCARD;
	new->str = NULL;
	new->next = NULL;
	new->ismatch = 0;
	new->prev = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	return (0);
}

int	ms_create_files(t_wcard **head, char *file)
{
	t_wcard	*new;
	t_wcard	*temp;

	temp = *head;
	new = malloc(sizeof(t_wcard));
	if (!new)
		return (errno);
	new->type = 0;
	new->ismatch = 0;
	new->str = NULL;
	if (file)
		new->str = ft_strdup(file);
	if (!new->str)
		return (errno);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	return (0);
}

void	ms_clean_wildcard(t_wcard *wcard, t_wcard *files)
{
	t_wcard	*temp1;
	t_wcard	*temp2;

	while (wcard)
	{
		temp1 = wcard->next;
		if (wcard->str)
			free(wcard->str);
		free(wcard);
		wcard = temp1;
	}
	while (files)
	{
		temp2 = files->next;
		free(files->str);
		free(files);
		files = temp2;
	}
}
