/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_format2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 11:59:31 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/08 12:15:14 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ms_format_tile(char *file_name, char **argve)
{
	char	*pwd;
	char	*file_path;
	int		size;

	pwd = getenv("HOME");
	size = ft_strlen(file_name) + ft_strlen(pwd) + 1;
	file_path = malloc(sizeof(char) * size);
	ft_strlcpy(file_path, pwd, ft_strlen(pwd) + 1);
	ft_strlcpy(file_path + ft_strlen(pwd), file_name, ft_strlen(file_name) + 1);
	free(pwd);
	return (file_path);
}

char	*ms_format_ds(char *file_name, char **argve)
{
	char	*pwd;
	char	*file_path;
	int		size;

	pwd = getenv("PWD");
	size = ft_strlen(file_name) + ft_strlen(pwd) - 1;
	file_path = malloc(sizeof(char) * size);
	ft_strlcpy(file_path, pwd, ft_strlen(pwd) + 1);
	ft_strlcpy(file_path + ft_strlen(pwd), file_name + 2,
		ft_strlen(file_name) - 1);
	free(pwd);
	return (file_path);
}

char	*ms_format_dd(char *file_name, char **argve)
{
	char	*pwd;
	char	*file_path;
	int		size;

	pwd = ms_find_path(argve, file_name);
	size = ft_strlen(file_name) + ft_strlen(pwd) + 1;
	file_path = malloc(sizeof(char) * size);
	ft_strlcpy(file_path, pwd, ft_strlen(pwd) + 1);
	ft_strlcpy(file_path + ft_strlen(pwd), file_name, ft_strlen(file_name) + 1);
	free(pwd);
	return (file_path);
}

char	*ms_format_sl(char *file_name, char **argve)
{
	char	*file_path;
	int		size;

	(void)argve;
	size = ft_strlen(file_name) + 1;
	file_path = malloc(sizeof(char) * size);
	ft_strlcpy(file_path, file_name, size);
	return (file_path);
}
