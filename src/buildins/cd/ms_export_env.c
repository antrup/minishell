/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:07:52 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/03 15:08:15 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

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
