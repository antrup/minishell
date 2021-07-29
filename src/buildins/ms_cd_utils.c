/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:01:15 by user42            #+#    #+#             */
/*   Updated: 2021/07/29 02:35:40 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static void	ms_join(char *path, char *target, char *str)
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

static int	ms_get_target_len(char *path)
{
	int	n;
	int	len;

	len = 0;
	n = ft_strlen(path) - 1;
	while (n)
	{
		if (path[n] == '/')
			break ;
		len++;
		n--;
	}
	return (len);
}

static char	*ms_get_target_name(char *path, int len)
{
	int	i;
	int	l;
	char *ret;

	i = 0;
	ret = malloc(sizeof(char) * (len + 1));
	l = ft_strlen(path);
	len = len - 1;
	while (len > -1)
	{
		ret[len] = path[l - 1];
		len--;
		l--;
	}
	return (ret);
}

char	*ms_add_target(char *dir, char *path)
{
	int		len;
	char	*target;
	char	*new_path;

	if (path == NULL)
		return (dir);
	len = ms_get_target_len(path);
	target = ms_get_target_name(path, len);
	new_path = malloc(sizeof(char) * (len + ft_strlen(dir) + 2));
	ms_join(path, target, new_path);
	return (new_path);
}

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

int	ms_absolute_path(char *path)
{
	char	*dir;
	char	*new_path;
	char	*old_path;
	int		ret;

	old_path = getenv("PWD");
	if (path[0] == '/')
	{
		ret = chdir(path);
		if (ret == -1)
			return (errno);
		ms_export_env(ft_strdup(path), old_path);
	}
	else if (path[0] != '/' && ms_has_slash(path))
	{
		dir = ms_get_directory(path, 0);
		new_path = malloc(sizeof(char)
			* (ft_strlen(path) + ft_strlen(dir) + 2));
		ms_join(dir, path, new_path);
		ret = chdir(new_path);
		free(new_path);
		free(dir);
		if (ret == -1)
			return (errno);
		ms_export_env(new_path, old_path);
	}
	else
	{
		ret = chdir(path);
		if (ret == -1)
			return (errno);
		ms_export_env(ft_strdup(path), old_path);
	}
	return (0);
}
