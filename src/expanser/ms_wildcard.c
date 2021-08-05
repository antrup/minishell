/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 02:42:55 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/05 04:57:02 by sshakya          ###   ########.fr       */
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
	return (NULL);
}

static int	ms_create_sterm(t_wcard **head, char *line, int *i, int count)
{
	t_wcard	*new;
	t_wcard *temp;

	temp = *head;
	new = malloc(sizeof(t_wcard));
	if (!new)
		return (errno);
	new->type = OP_STERM;
	new->str = ms_part(line, i, count);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}

static int ms_create_wcard(t_wcard **head, int *i, int *count)
{
	t_wcard	*new;
	t_wcard *temp;

	temp = *head;
	new = malloc(sizeof(t_wcard));
	if (!new)
		return (errno);
	*count += 1;
	*i += 1;
	new->type = OP_WCARD;
	new->str = NULL;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}

static int ms_make_wtokens(char *line, t_wcard **wc)
{
	int		count;
	int		err;
	int		i;

	count = 0;
	err = 0;
	i = 0;
	while (line[i] && !err)
	{
		if (line[i] == '*')
			err = ms_create_wcard(wc, &i, &count);
		else
			err = ms_create_sterm(wc, line, &i, count);
	}
	return (err);
}

static int	ms_create_files(t_word **head, char *file)
{
	t_word	*new;
	t_word *temp;

	temp = *head;
	new = malloc(sizeof(t_wcard));
	if (!new)
		return (errno);
	new->part = ft_strdup(file);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}

static int ms_make_ftokens(t_word **files)
{
	DIR	*dp;
	struct dirent *ep;

	dp = opendir ("./");
	if (dp != NULL)
	{
		ep = readdir(dp);
		while (ep)
			ms_create_files(files, ep->d_name);
		(void)closedir(dp);
	}
	else
		return (errno);
	return (0);
}

static int print_test(t_wcard *wcard, t_word *files)
{
	while (wcard)
	{
		if (wcard->type == OP_WCARD)
			printf("*\t");
		else
			printf("%s\t", wcard->str);
		wcard = wcard->next;
	}

	while (files)
	{
		printf("%s\t", files->part);
		files = files->next;
	}
	return (0);
}

int	ms_wildcard(t_tlist **head, t_tlist *token)
{
	t_wcard	*wcard;
	t_word	*files;

	wcard = NULL;
	files = NULL;
	(void)head;
	ms_make_wtokens(token->tk.value, &wcard);
	ms_make_ftokens(&files);
	print_test(wcard, files);
	return (0);
}	