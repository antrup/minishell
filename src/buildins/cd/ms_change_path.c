/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_change_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 20:46:59 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/03 15:05:15 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_has_slash(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static int	ms_absolute_path(char *path)
{
	int		error;
	char	*old_path;
	char	*new_path;

	old_path = NULL;
	new_path = NULL;
	old_path = ms_get_directory(path, CD_CURRENT);
	new_path = ft_strdup(path);
	error = chdir(path);
	if (error == -1)
		return (ms_error_nav(old_path, new_path, errno));
	ms_export_env(new_path, old_path);
	return (0);
}

static int	ms_current_path(char *path)
{
	int		error;
	char	*old_path;
	char	*new_path;

	old_path = NULL;
	new_path = NULL;
	old_path = ms_get_directory(path, CD_CURRENT);
	new_path = malloc(sizeof(char)
			* (ft_strlen(path) + ft_strlen(old_path) + 2));
	if (!new_path)
		return (errno);
	ms_slash_join(old_path, path, new_path);
	error = chdir(new_path);
	if (error == -1)
		return (ms_error_nav(old_path, new_path, errno));
	ms_export_env(new_path, old_path);
	return (0);
}

static int	ms_current_folder(char *path)
{
	char	*old_path;
	char	*new_path;
	int		error;

	old_path = NULL;
	new_path = NULL;
	error = chdir(path);
	if (error == -1)
		return (errno);
	old_path = ms_get_directory(path, CD_CURRENT);
	new_path = malloc(sizeof(char)
			* (ft_strlen(path) + ft_strlen(old_path) + 2));
	if (!new_path)
		return (ms_error_nav(old_path, new_path, errno));
	ms_slash_join(old_path, path, new_path);
	ms_export_env(new_path, old_path);
	return (0);
}

int	ms_change_path(char *path)
{
	int	error;

	error = 0;
	if (path[0] == '/')
		error = ms_absolute_path(path);
	else if (path[0] != '/' && ms_has_slash(path))
		error = ms_current_path(path);
	else
		error = ms_current_folder(path);
	return (error);
}
