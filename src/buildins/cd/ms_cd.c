/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:06:45 by user42            #+#    #+#             */
/*   Updated: 2021/08/03 16:24:31 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_cd_error(int error)
{
	char	*err_str;

	if (error == ERR_CD)
	{
		write (2, "MyShell: cd: too many arguments\n", 32);
		return (1);
	}
	err_str = strerror(error);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(err_str, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	ms_cd(char **args)
{
	int	error;

	error = 0;
	if (args[0] != NULL && args[1] != NULL)
		return (ms_cd_error(ERR_CD));
	if (args[0] == NULL)
	{
		error = ms_navigate_home(args[0]);
		if (error)
			return (ms_cd_error(error));
	}
	else if (ms_isrelative(args[0]) == CD_NOT)
	{
		error = ms_change_path(args[0]);
		if (error)
			return (ms_cd_error(error));
	}
	else
	{
		error = ms_relative_path(args[0]);
		if (error)
			return (ms_cd_error(error));
	}
	return (0);
}
