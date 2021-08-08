/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 02:42:55 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/08 12:47:42 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_iswildcard(char *line)
{
	int	y;

	y = 0;
	while (line[y])
	{
		if (line[y] == '*')
			return (1);
		y++;
	}
	return (0);
}

static int	ms_make_wtokens(char *line, t_wcard **wc)
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
		{	
			while (line[i] == '*')
				i++;
			i--;
			err = ms_create_wcard(wc, &i, &count);
		}
		else
			err = ms_create_sterm(wc, line, &i, count);
	}
	return (err);
}

static int	ms_make_ftokens(t_wcard **files)
{
	DIR				*dp;
	struct dirent	*ep;

	dp = opendir ("./");
	if (dp != NULL)
	{
		ep = readdir(dp);
		while (ep != NULL)
		{
			ms_create_files(files, ep->d_name);
			ep = readdir(dp);
		}
		(void)closedir(dp);
	}
	else
		return (errno);
	return (0);
}

static int	ms_cmatch_list(t_tlist **head, t_tlist **current, t_wcard *files)
{
	t_tlist	*iswild;
	t_tlist	*matches;
	t_tlist	*next;

	matches = NULL;
	next = NULL;
	ms_ctoken_matches(&matches, files);
	iswild = ms_iswild(head);
	if (!matches)
		return (-1);
	next = ms_insert_matches(head, matches, iswild);
	while (matches->next)
		matches = matches->next;
	matches->next = next;
	if (matches)
	{
		free(iswild->tk.value);
		free(iswild);
		*current = matches;
	}
	return (0);
}

int	ms_wildcard(t_tlist **token, t_tlist **head)
{
	t_wcard	*wcard;
	t_wcard	*files;
	int		err;

	wcard = NULL;
	files = NULL;
	err = 0;
	err = ms_make_wtokens((*token)->tk.value, &wcard);
	if (err)
		return (err);
	err = ms_make_ftokens(&files);
	ms_sort_files(files);
	if (err)
		return (err);
	err = ms_find_matches(wcard, files);
	if (err)
		return (err);
	err = ms_cmatch_list(head, token, files);
	if (err)
		return (err);
	ms_clean_wildcard(wcard, files);
	return (0);
}
