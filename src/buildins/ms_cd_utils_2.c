/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 19:09:18 by user42            #+#    #+#             */
/*   Updated: 2021/07/29 02:37:14 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

char	*ms_get_directory(char *path, int relative)
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
	if (relative == 0)
		return (ft_strdup(pwd));
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

int	ms_export_env(char *path, char *old_path)
{
	char	**ex_path_new;
	char	**ex_path_old;
	
	ex_path_new = malloc(sizeof(char *) * 2);
	if (ex_path_new == NULL)
		return (ERR_MEM);
	ex_path_new[0] = ft_strjoin("PWD=", path);
	ex_path_new[1] = NULL;
	ms_export(ex_path_new);
	ex_path_old = malloc(sizeof(char *) * 2);
	if (ex_path_new == NULL)
		return (ERR_MEM);
	ex_path_old[0] = ft_strjoin("OLDPWD=", old_path);
	ex_path_old[1] = NULL;
	ms_export(ex_path_old);
	free(ex_path_new[0]);
	free(ex_path_new[1]);
	free(ex_path_new);
	free(ex_path_old[0]);
	free(ex_path_old[1]);
	free(ex_path_old);
	free(path);
	return (0);
}

void	ms_navigate_up(char *path)
{
	char	*dir;
	char	*new_path;
	char	*old_path;

	dir = ms_get_directory(path, 1);
	new_path = ms_add_target(dir, path);
	old_path = getenv("PWD");
	chdir(new_path);
	ms_export_env(new_path, old_path);
	free(new_path);
	free(dir);
}
