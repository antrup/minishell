/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:01:15 by user42            #+#    #+#             */
/*   Updated: 2021/07/30 15:38:22 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_isrelative(char *arg)
{
	if (arg[0] == '.' && arg[1] == '\0')
		return (CD_NONE);
	if (arg[0] == '.' && arg[1] == '/')
		return (CD_CURRENT_R);
	if (arg[0] == '.' && arg[1] == '.' && arg[2] == '/')
		return (CD_RELATIVE);
	if (arg[0] == '.' && arg[1] == '.' && arg[2] == '\0')
		return (CD_UP_ONE);
	if (arg[0] == '~' && arg[1] == '/')
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

static void	ms_clean_exp(char **path)
{
	free(path[0]);
	free(path[1]);
	free(path);
}

int	ms_export_env(char *path, char *old_path)
{
	char	**ex_path_new;
	char	**ex_path_old;
	
	ex_path_new = malloc(sizeof(char *) * 2);
	if (ex_path_new == NULL)
		return (ERR_MEM);
	ex_path_new[0] = ft_strjoin("PWD=", path);
	ex_path_new[1] = NULL;
	free(path);
	ms_export(ex_path_new);
	ms_clean_exp(ex_path_new);
	ex_path_old = malloc(sizeof(char *) * 2);
	if (ex_path_new == NULL)
		return (ERR_MEM);
	ex_path_old[0] = ft_strjoin("OLDPWD=", old_path);
	ex_path_old[1] = NULL;
	free(old_path);
	ms_export(ex_path_old);
	ms_clean_exp(ex_path_old);
	return (0);
}

int	ms_error_nav(char *path1, char *path2, int error)
{
	free(path1);
	free(path2);
	return (error);
}
