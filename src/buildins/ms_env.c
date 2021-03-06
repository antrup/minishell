/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:01:22 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/28 18:06:10 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_env(void)
{
	int		i;

	i = 0;
	while (environ[i])
	{
		write(1, environ[i], ft_strlen(environ[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
