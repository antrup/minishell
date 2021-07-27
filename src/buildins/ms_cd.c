/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:06:45 by user42            #+#    #+#             */
/*   Updated: 2021/07/27 20:04:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_isrelative(char *arg)
{
	if (arg && arg[0] == '.' && arg[1] == '\0')
		return (1);
	if (arg && arg[0] == '.' && arg[1] != '.' && arg[2] == '\0')
		return (2);
	if (arg && arg[0] == '.' && arg[1] == '/')
		return (3);
	if (arg && arg[0] == '.' && arg[1] == '.' && arg[2] == '/')
		return (4);
	if (arg && arg[0] == '~' && arg[1] == '/')
		return (5);
	return (0);
}	

static int	ms_change_dir(char *path)
{
	int		type;

	dir = NULL;
	type = ms_isrelative(path);
	if (type == 1 || type == 3)
		return (0);
	if (type == 2)
		ms_navigate_up_one(path);
	if (type == 4)
		ms_navigate_up(path);
	if (type == 5)
		ms_navigate_home(path);
	return (0);
}

int	ms_cd(char **args)
{
	if (args[1] != NULL)
		return (ERR_CD);
	if (ms_isrelative(args[0]) == 0)
	{
		chdir(args[0]);
		ms_export_env(args[0]);
		return (0);
	}
	else
		ms_change_dir(args[0]);
	return (0);
}
