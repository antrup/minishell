/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 11:21:30 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/22 11:57:41 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ms_echo_option(int *i, char **args)
{
	int		n_opt,
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
				n_opt = 0;
				stop = 1;
				break;
			}
			y++;
		}
		if (!stop)
		(*i)++;
	return (n_opt);
}

void	ms_echo(char **args)
{
	int		n_opt;
	int		i;

	n_opt = ms_echo_option(&i, args);
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		i++;
	}
	if (!n_opt)
		write(1, "\n", 1);
	return ;
}