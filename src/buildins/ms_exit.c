/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 11:36:10 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/07 00:30:49 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_exit_error(char *arg, int type)
{
	if (type == 1)
	{
		write(2, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 36);
	}
	if (type == 2)
	{
		write(2, "minishell: exit: ", 16);
		write(2, arg, ft_strlen(arg));
		write(2, " : numeric argument required\n", 29);
		ms_clean(g_shell.data);
		exit(1);
	}
	return (1);
}

int	ms_exit(char **args)
{
	int	ret;
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	ret = 0;
	if (!args[0])
	{
		ms_clean(g_shell.data);
		exit(ret);
	}
	if (args[1])
		return (ms_exit_error(args[0], 1));
	while (args[0] && args[0][i])
	{
		if (!ft_isdigit(args[0][i]))
		{
			flag = 1;
			ret = 0;
		}
		i++;
	}
	if (!flag)
	{
		ret = ft_atoi(args[0]);
		ms_clean(g_shell.data);
		exit(ret);
	}
	if (flag)
		return (ms_exit_error(args[0], 2));
	return (0);
}
