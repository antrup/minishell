/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 02:42:55 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/05 19:05:27 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

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

static int ms_make_ftokens(t_wcard **files)
{
	DIR	*dp;
	struct dirent *ep;

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
/*
static int print_test(t_wcard *wcard, t_wcard *files)
{
	t_wcard *temp;
	t_wcard *temp1;

	printf("WILDCARDS\n");
	while (wcard)
	{
		temp = wcard->next;
		if (wcard->type == OP_WCARD)
			printf("*\n");
		else
			printf("%s\n", wcard->str);
		wcard = temp;
	}
	printf("\n");
	printf("FILES\n");
	while (files)
	{
		temp1 = files->next;
		printf("%s\t", files->str);
		if (files->ismatch == 1)
			printf("ismatch\n");
		else
			printf("nomatch\n");
		files = temp1;
	}
	printf("\n");
	return (0);
}
*/
static int	ms_ctoken_matches(t_tlist **wtoken, t_wcard *files)
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

static int	ms_cmatch_list(t_tlist **head, t_wcard *files)
{
	t_tlist	*iswild;
	t_tlist	*matches;
	t_tlist	*next;

	iswild = *head;
	matches = NULL;
	next = NULL;
	while (iswild)
	{
		if (iswild->tk.type == WORD && ms_iswildcard(iswild->tk.value))
			break ;
		iswild = iswild->next;
	}
	ms_ctoken_matches(&matches, files);
	if (!matches)
		return (-1);
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
	while (matches->next)
		matches = matches->next;
	matches->next = next;
	return (0);
}

int	ms_wildcard(t_tlist **token, t_tlist **head)
{
	t_wcard	*wcard;
	t_wcard	*files;
	t_tlist	*match;
	int		err;

	wcard = NULL;
	files = NULL;
	match = NULL;
	err = 0;
	err = ms_make_wtokens((*token)->tk.value, &wcard);
	if (err)
		return (err);
	err = ms_make_ftokens(&files);
	if (err)
		return (err);
	err = ms_find_matches(wcard, files);
	err = ms_cmatch_list(head, files);
	//print_test(wcard, files);
	ms_clean_wildcard(wcard, files);
	if (match)
	{
		free((*token)->tk.value);
		free(*token);
		*token = match;
	}
	return (0);
}	
