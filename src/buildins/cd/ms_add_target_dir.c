/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_target_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 22:08:11 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/29 22:08:44 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

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

char	*ms_add_target_dir(char *dir, char *path)
{
	int		len;
	char	*target;
	char	*new_path;

	if (path == NULL)
		return (dir);
	len = ms_get_target_len(path);
	target = ms_get_target_name(path, len);
	new_path = malloc(sizeof(char) * (len + ft_strlen(dir) + 2));
	ms_slash_join(path, target, new_path);
	return (new_path);
}
