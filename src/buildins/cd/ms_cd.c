/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:06:45 by user42            #+#    #+#             */
/*   Updated: 2021/07/30 13:18:57 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_cd(char **args)
{
	int	error;

	error = 0;
	if (args[0] == NULL)
		return (0);
	if (args[1] != NULL)
		return (ERR_CD);
	if (ms_isrelative(args[0]) == CD_NOT)
	{
		error = ms_change_path(args[0]);
		if (!error)
			return (0);
	}
	else
	{
		error =	ms_relative_path(args[0]);
		if (!error)
			return (0);
	}
	if (error > 0)
		printf("%s\n", strerror(error));
	return (error);
}
