/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcard_matches.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 17:21:58 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/06 21:04:00 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_ismatch(t_wcard *files, t_wcard *wcard, int show_hidden)
{
	char	*temp;
	int		flag;

	temp = files->str;
	flag = 0;
	if ((!show_hidden && files->str[0] == '.'))
		return (0);
	while (temp && temp[0] != '\0')
	{	
		if (!wcard->prev && strncmp(temp, wcard->str, ft_strlen(wcard->str)))
			return (0);
		if (!strncmp(temp, wcard->str, ft_strlen(wcard->str)))
		{
			if (!wcard->next && *(temp + ft_strlen(wcard->str)) != '\0')
				return (0);
			return (1);
		}
		temp++;
	}
	return (0);
}

static int	ms_show_hidden(t_wcard *wcard)
{
	if (wcard->type == OP_STERM
		&& wcard->str[0] == '.' && wcard->str[1] == '\0')
		return (1);
	return (0);
}

static int	ms_showall(t_wcard *wcard)
{
	if (wcard->type == OP_WCARD
		&& wcard->next == NULL && wcard->prev == NULL)
		return (1);
	return (0);
}

static int	ms_ishidden(char *file)
{
	if (file[0] == '.')
		return (1);
	return (0);
}

int	ms_find_matches(t_wcard *wcard, t_wcard *files)
{
	t_wcard	*twcard;

	while (files)
	{
		twcard = wcard;
		while (twcard)
		{
			if (twcard->type == OP_WCARD && !ms_showall(wcard))
				twcard = twcard->next;
			if (!twcard && !ms_showall(wcard))
				break ;
			if ((ms_showall(wcard) && !ms_ishidden(files->str))
				|| ms_ismatch(files, twcard, ms_show_hidden(wcard)))
				files->ismatch = 1;
			else
			{
				files->ismatch = 0;
				break ;
			}
			twcard = twcard->next;
		}
		files = files->next;
	}
	return (0);
}
