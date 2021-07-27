/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:01:15 by user42            #+#    #+#             */
/*   Updated: 2021/07/27 19:09:37 by user42           ###   ########.fr       */
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
		new_path[i] = path[i];
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
	while (len)
	{
		ret[i] = path[l - 1];
		l--;
	}
	return (ret);
}

char	*ms_add_target(char *dir, char *path)
{
	int		i;
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
