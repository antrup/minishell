/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_relative_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 19:09:18 by user42            #+#    #+#             */
/*   Updated: 2021/07/29 23:43:55 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_navigate_up(char *target)
{
	int		error;
	char	*new_path;
	char	*old_path;

	old_path = ms_get_directory(target, CD_CURRENT);
	new_path = ms_add_target_dir(old_path, target);
	error = chdir(new_path);
	if (error)
		return (ms_error_nav(old_path, new_path, ERR_CD));
	ms_export_env(new_path, old_path);
	return (0);
}

static int ms_navigate_up_one(char *target)
{
	int		error;
	char	*new_path;
	char	*old_path;

	old_path = ms_get_directory(target, CD_CURRENT);
	new_path = ms_add_target_dir(old_path, target);
	error = chdir(new_path);
	if (error)
		return (ms_error_nav(old_path, new_path, ERR_CD));
	ms_export_env(new_path, old_path);
	return (0);
}

static int	ms_navigate_current(char *path)
{
	(void)path;
	return (0);
}

static int	ms_navigate_home(char *path)
{
	(void)path;
	return (0);
}

int	ms_relative_path(char *path)
{
	int		type;
	int		error;

	error = 0;
	type = ms_isrelative(path);
	printf("%d\n", type);
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
	if (error)
		return (error);
	return (0);
}

