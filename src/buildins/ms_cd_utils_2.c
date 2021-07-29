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

char	*ms_get_directory(char *path)
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

int	ms_export_env(char *path)
{
	char	**ex_path;
	
	ex_path = malloc(sizeof(char *) * 2);
	if (ex_path == NULL)
		return (ERR_MEM);
	ex_path[0] = ft_strjoin(path, "PATH=");
	ex_path[1] = NULL;
	free(ex_path[0]);
	free(ex_path[1]);
	free(ex_path);
	return (0);
}

void	ms_navigate_up(char *path)
{
	char	*dir;
	char	*new_path;

	dir = ms_get_directory(path);
	new_path = ms_add_target(dir, path);
	chdir(new_path);
	ms_export_env(new_path);
	free(new_path);
	free(dir);
}
