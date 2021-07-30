/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_relative_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 19:09:18 by user42            #+#    #+#             */
/*   Updated: 2021/07/30 14:08:44 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_navigate_up(char *target)
{
	int		error;
	char	*new_path;
	char	*dir;
	char	*old_path;

	new_path = NULL;
	old_path = NULL;
	dir = NULL;
	old_path = ms_get_directory(target, CD_CURRENT);
	dir = ms_get_directory(target, CD_RELATIVE);	
	new_path = ms_add_target_dir(dir, target);
	free(dir);
	error = chdir(new_path);
	if (error)
		return (ms_error_nav(old_path, new_path, errno));
	ms_export_env(new_path, old_path);
	return (0);
}

static int ms_navigate_up_one(char *target)
{
	int		error;
	char	*new_path;
	char	*old_path;

	new_path = NULL;
	old_path = NULL;
	old_path = ms_get_directory(target, CD_CURRENT);
	new_path = ms_get_directory(target, CD_UP_ONE);
	error = chdir(new_path);
	if (error)
		return (ms_error_nav(old_path, new_path, errno));
	ms_export_env(new_path, old_path);
	return (0);
}

static int	ms_navigate_current(char *target)
{
	int		error;
	char	*new_path;
	char	*old_path;

	new_path = NULL;
	old_path = NULL;
	old_path = ms_get_directory(target, CD_CURRENT);
	new_path = ms_add_target_dir(old_path, target);
	error = chdir(new_path);
	if (error)
		return (ms_error_nav(old_path, new_path, errno));
	ms_export_env(new_path, old_path);
	return (0);
}

static int	ms_navigate_home(char *target)
{	
	int		error;
	char	*new_path;
	char	*old_path;
	char	*home;

	new_path = NULL;
	old_path = NULL;
	home = NULL;
	old_path = ms_get_directory(target, CD_CURRENT);
	home = ms_get_directory(target, CD_HOME);
	new_path = ms_add_target_dir(home, target);
	free(home);
	error = chdir(new_path);
	if (error)
		return (ms_error_nav(old_path, new_path, errno));
	ms_export_env(new_path, old_path);
	return (0);
}

static int	ms_navigate_back(void)
{
	int	error;
	char	*new_path;
	char	*old_path;

	new_path = NULL;
	old_path = NULL;
	error = 0;
	new_path = ms_get_directory(NULL, CD_BACK);
	old_path = ms_get_directory(NULL, CD_CURRENT);
	if (new_path == NULL)
		return (0);
	error = chdir(new_path);
	if (error)
		return (ms_error_nav(old_path, new_path, errno));
	ms_export_env(new_path, old_path);
	return (0);
}

int	ms_relative_path(char *path)
{
	int		type;
	int		error;

	error = 0;
	type = ms_isrelative(path);
	if (type == CD_NONE)
		return (0);
	if (type == CD_UP_ONE)
		error = ms_navigate_up_one(path);
	if (type == CD_CURRENT_R)
		error = ms_navigate_current(path);
	if (type == CD_RELATIVE)
		error = ms_navigate_up(path);
	if (type == CD_HOME)
		error = ms_navigate_home(path);
	if (type == CD_BACK)
		error = ms_navigate_back();
	if (error)
		return (error);
	return (0);
}
