/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:01:15 by user42            #+#    #+#             */
/*   Updated: 2021/08/03 16:25:15 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_isrelative(char *arg)
{	
	char	*test;

	test = getenv("PWD");
	if (test == NULL)
		return (errno);
	if (test[0] == '/' && test[1] == '\0')
		return (0);
	if (arg[0] == '.' && arg[1] == '\0')
		return (CD_NONE);
	if (arg[0] == '.' && arg[1] == '/')
		return (CD_CURRENT_R);
	if (arg[0] == '.' && arg[1] == '.' && arg[2] == '/')
		return (CD_RELATIVE);
	if (arg[0] == '.' && arg[1] == '.' && arg[2] == '\0')
		return (CD_UP_ONE);
	if (arg[0] == '~' && (arg[1] == '/' || arg[1] == '\0'))
		return (CD_HOME);
	if (arg[0] == '-')
		return (CD_BACK);
	return (CD_NOT);
}

void	ms_slash_join(char *path, char *target, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (path && path[i] != '\0')
	{
		str[i] = path[i];
		i++;
	}
	str[i] = '/';
	j = 0;
	i++;
	while (target[j] != '\0')
	{
		str[i] = target[j];
		i++;
		j++;
	}
	str[i] = '\0';
}

int	ms_error_nav(char *path1, char *path2, int error)
{
	free(path1);
	free(path2);
	return (error);
}

int	ms_navigate_home(char *target)
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
	if (target && target[0] == '~' && target[1] != '\0')
		free(home);
	error = chdir(new_path);
	if (error)
		return (ms_error_nav(old_path, new_path, errno));
	ms_export_env(new_path, old_path);
	return (0);
}

char	*ms_get_home_dir(void)
{
	char	*home;

	home = NULL;
	home = getenv("HOME");
	if (!home)
		return (NULL);
	home = ft_strdup(home);
	return (home);
}
