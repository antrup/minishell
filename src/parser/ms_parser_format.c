/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 11:55:38 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/08 17:46:18 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_format_cmd(char *file_name)
{
	char	*file_path;
	char	**tab_path;
	int		size_name;

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
	{	
		tab_path = ms_ext_path();
		size_name = ms_name_sizer(file_name);
		file_path = ms_find_cmd_path(file_name, &tab_path, size_name);
	}
	return (file_path);
}

char	*ms_format_file(char *file_name)
{
	char	*pwd;
	char	*file_path;
	int		size;

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
	{
		pwd = getenv("PWD");
		size = ft_strlen(file_name) + ft_strlen(pwd) + 1;
		file_path = malloc(sizeof(char) * size);
		ft_strlcpy(file_path, pwd, ft_strlen(pwd) + 1);
		ft_strlcpy(file_path + ft_strlen(pwd), file_name,
			ft_strlen(file_name) + 1);
	}
	return (file_path);
}