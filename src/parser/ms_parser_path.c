/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:27:04 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/21 09:59:41 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

char	*ms_find_cmd_path(char	*cmd_name, char ***t_path, int size_n)
{	
	int			i;
	int			size;
	char		*cmd_path;
	struct stat sf;

	i = 0;
	while (t_path[0][i])
	{
		size = ft_strlen(cmd_name) + ft_strlen(t_path[0][i]) + 1;
		cmd_path = malloc(sizeof(char) * size);
		if (!cmd_path)
			return (ms_clean_tab_path(t_path, NULL));
		ft_strlcpy(cmd_path, t_path[0][i], ft_strlen(t_path[0][i]) + 1);
		ft_strlcpy(cmd_path + ft_strlen(t_path[0][i]), cmd_name, size_n + 1);
		if (stat(cmd_path, &sf) == 0 && sf.st_mode & S_IXUSR)
		{	
			if (ft_strlen(cmd_name) > (unsigned long)size_n)
				ft_strlcpy(cmd_path + ft_strlen(t_path[0][i]) + size_n, cmd_name
					+ size_n, ft_strlen(cmd_name) - size_n + 1);
			return (ms_clean_tab_path(t_path, cmd_path));
		}
		free(cmd_path);
		i++;
	}
	return (ms_clean_tab_path(t_path, NULL));
}

char	*ms_find_path(char *file_name)
{
	int		level;
	char	*pwd;
	char	*path;
	int		i;

	level = 0;
	i = 0;
	while (file_name[i] == '.' && file_name[i + 1] == '.'
		&& file_name[i + 2] == '/')
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
	path = malloc(sizeof(char) * (i + 2));
	ft_strlcpy(pwd, path, i + 2);
	return (path);
}
