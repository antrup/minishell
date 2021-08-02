/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_format2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 11:59:31 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/02 16:45:14 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

/*
** TILDE
*/
char	*ms_format_tile(char *file_name)
{
	char	*pwd;
	char	*file_path;
	int		size;

	pwd = getenv("HOME");
	if (!pwd)
		return (ft_strdup(file_name));
	size = ft_strlen(file_name) + ft_strlen(pwd) + 1;
	file_path = malloc(sizeof(char) * size);
	ft_strlcpy(file_path, pwd, ft_strlen(pwd) + 1);
	ft_strlcpy(file_path + ft_strlen(pwd), file_name, ft_strlen(file_name) + 1);
	return (file_path);
}

/*
** SINGLE DOT
*/
char	*ms_format_ds(char *file_name)
{
	char	*pwd;
	char	*file_path;
	int		size;

	pwd = getenv("PWD");
	size = ft_strlen(file_name) + ft_strlen(pwd);
	file_path = malloc(sizeof(char) * size);
	ft_strlcpy(file_path, pwd, ft_strlen(pwd) + 1);
	ft_strlcpy(file_path + ft_strlen(pwd), "/", 2);
	ft_strlcpy(file_path + ft_strlen(pwd) + 1, file_name + 2,
		ft_strlen(file_name) - 1);
	return (file_path);
}

/*
** DOUBLE DOT
*/
char	*ms_format_dd(char *file_name)
{
	char	*pwd;
	char	*file_path;
	int		size;
	int		n;

	n = 0;
	pwd = ms_find_path(file_name);
	size = ft_strlen(file_name) + ft_strlen(pwd) + 2;
	file_path = malloc(sizeof(char) * size);
	while (*file_name == '.' && *(file_name + 1) == '.' && *(file_name + 2) == '/')
	{
		file_name = file_name + 3;
		n++;
	}
	if (n == 1 && ft_strlen(file_name - 3) == 3)
		return (NULL);
	ft_strlcpy(file_path, pwd, ft_strlen(pwd) + 1);
	if (!(file_path[0] == '/' && file_path[1] == '\0'))
	{	
		ft_strlcpy(file_path + ft_strlen(pwd), "/", 2);
		ft_strlcpy(file_path + ft_strlen(pwd) + 1, file_name, ft_strlen(file_name) + 1);
	}
	else
		ft_strlcpy(file_path + ft_strlen(pwd), file_name, ft_strlen(file_name) + 1);
	free(pwd);
	return (file_path);
}

/*
** SLASH
*/

char	*ms_format_sl(char *file_name)
{
	char	*file_path;
	int		size;

	size = ft_strlen(file_name) + 1;
	file_path = malloc(sizeof(char) * size);
	ft_strlcpy(file_path, file_name, size);
	return (file_path);
}
