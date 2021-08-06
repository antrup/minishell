/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 11:21:30 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/06 14:02:40 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_echo_option(int *i, char **args)
{
	int		n_opt;
	int		y;
	int		stop;

	n_opt = 0;
	stop = 0;
	while (!stop && !ft_strncmp(args[*i], "-n", 2))
	{
		n_opt = 1;
		y = 2;
		while (args[*i][y])
		{
			if (args[*i][y] != 'n')
			{
				if (*i == 0)
					n_opt = 0;
				stop = 1;
				break ;
			}
			y++;
		}
		if (!stop)
			(*i)++;
	}
	return (n_opt);
}

int	ms_echo(char **args)
{
	int		n_opt;
	int		i;

	i = 0;
	if (!args[0])
		n_opt = 0;
	else
		n_opt = ms_echo_option(&i, args);
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_opt)
		write(1, "\n", 1);
	return (0);
}
