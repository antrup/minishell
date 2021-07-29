/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 20:37:13 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/29 23:16:34 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static char	*ms_get_relative_dir(char *path)
{
	int		level;
	char	*pwd;
	char	*dir;
	int		i;

	level = 0;
	i = 0;
	while (path[i] == '.' && path[i + 1] == '.' && path[i + 2] == '/')
	{
		level++;
		i = i + 3;
	}
	pwd = getenv("PWD");
	i = ft_strlen(pwd) - 2;
	while (level && i)
	{
		if (pwd[i] == '/')
			level--;
		i--;
	}
	dir = malloc(sizeof(char) * (i + 2));
	ft_strlcpy(dir, pwd, i + 2);
	return (dir);
}

static char	*ms_get_home_dir(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		return (NULL);
	home = ft_strdup(home);
	return (home);
}

static char	*ms_get_current_dir(void)
{
	char	*current;

	current = getenv("PWD");
	if (!current)
		return (NULL);
	current = ft_strdup(current);
	if (!current)
		return (NULL);
	return (current);
}

char	*ms_get_directory(char *path, int relative)
{
	char	*dir;

	dir = NULL;
	if (relative == CD_CURRENT)
		dir = ms_get_current_dir();
	if (relative == CD_HOME)
		dir = ms_get_home_dir();
	if (relative == CD_RELATIVE)
		dir = ms_get_relative_dir(path);
	return (dir);
}


