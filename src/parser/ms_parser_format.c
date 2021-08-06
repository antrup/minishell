/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 11:55:38 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/06 18:10:15 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static char	*ms_format_slash(char *name)
{
	char	*file_path;
	int		size_name;
	char	*pwd;

	pwd = getenv("PWD");
	size_name = ft_strlen(name) + ft_strlen(pwd) + 2;
	file_path = malloc(sizeof(char) * size_name);
	ft_strlcpy(file_path, pwd, ft_strlen(pwd) + 1);
	ft_strlcpy(file_path + ft_strlen(pwd), "/", 2);
	ft_strlcpy(file_path + ft_strlen(pwd) + 1, file_name, ft_strlen(name) + 1);
	return (file_path);
}

static char	*ms_format_cmd_path(char *file_name)
{
	char	*file_path;
	char	**tab_path;
	int		size_name;

	tab_path = ms_ext_path();
	if (!tab_path)
		return (ft_strdup(file_name));
	size_name = ms_name_sizer(file_name);
	file_path = ms_find_cmd_path(file_name, &tab_path, size_name);
	return (file_path);
}

char	*ms_format_cmd(char *file_name)
{
	char	*file_path;
	char	**tab_path;
	int		size_name;

	if (file_name[0] == '\0')
		return (ft_strdup(""));
	if (file_name[0] == '/')
		return (ms_format_sl(file_name));
	else if (file_name[0] == '~' && file_name[1] == '/')
		return (ms_format_tile(file_name));
	else if ((file_name[0] == '.' && file_name[1] == '/'))
		return (ms_format_ds(file_name));
	else if ((file_name[0] == '.' && file_name[1] == '.'
			&& file_name[2] == '/'))
		return (ms_format_dd(file_name));
	else if (ms_has_slash(file_name))
		return (ms_format_slash(file_name));
	else
		return (ms_format_cmd_path(file_name));
}

static char	*ms_format_file_naked(char *file_name)
{
	char	*pwd;
	char	*file_path;
	int		size;

	pwd = getenv("PWD");
	size = ft_strlen(file_name) + ft_strlen(pwd) + 2;
	file_path = malloc(sizeof(char) * size);
	ft_strlcpy(file_path, pwd, ft_strlen(pwd) + 1);
	ft_strlcpy(file_path + ft_strlen(pwd), "/", 2);
	ft_strlcpy(file_path + ft_strlen(pwd) + 1, file_name,
		ft_strlen(file_name) + 1);
	return (file_path);
}

char	*ms_format_file(char *file_name)
{
	char	*pwd;
	char	*file_path;
	int		size;

	if (file_name[0] == '\0')
		return (ft_strdup(""));
	if (file_name[0] == '/')
		return (ms_format_sl(file_name));
	else if (file_name[0] == '~' && file_name[1] == '/')
		return (ms_format_tile(file_name));
	else if ((file_name[0] == '.' && file_name[1] == '/'))
		return (ms_format_ds(file_name));
	else if ((file_name[0] == '.' && file_name[1] == '.'
			&& file_name[2] == '/'))
		return (ms_format_dd(file_name));
	else
		return (ms_format_file_naked(file_name));
}
