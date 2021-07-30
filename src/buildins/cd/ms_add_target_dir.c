/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_target_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 22:08:11 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/30 13:53:59 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_get_target_len(char *path)
{
	int	n;
	int	len;
	int	end;

	len = 0;
	n = ft_strlen(path) - 1;
	end = n;
	while (n)
	{
		if (end != n && path[n] == '/')
			break ;
		len++;
		n--;
	}
	return (len);
}

static char	*ms_strip_tslash(char *target)
{
	int		len;
	char	*new_target;

	len = ft_strlen(target) - 1;
	if (target[len] == '/')
	{
		new_target = malloc(sizeof(char) * (len + 1));
		ft_strlcpy(new_target, target, len + 1);
		free(target);
		return (new_target);
	}
	return (target);
}


static char	*ms_get_target_name(char *path, int len)
{
	int		i;
	int		l;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * (len + 1));
	l = ft_strlen(path);
	while (len > -1)
	{
		ret[len] = path[l];
		len--;
		l--;
	}
	ret = ms_strip_tslash(ret);
	return (ret);
}

char	*ms_add_target_dir(char *dir, char *path)
{
	int		len;
	char	*target;
	char	*new_path;

	if (path == NULL)
		return (dir);
	len = ms_get_target_len(path);
	target = ms_get_target_name(path, len);
	printf("%s\n", dir);
	printf("%s\n", path);
	printf("%s\n", target);
	new_path = malloc(sizeof(char) * (len + ft_strlen(dir) + 2));
	ms_slash_join(dir, target, new_path);
	free(target);
	return (new_path);
}
