/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_expanser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 17:29:25 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/09 17:33:03 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	t_ms data;
	char *ret;
	
	ft_memset(data, 0, sizeof(t_ms));
	ret = ms_expanser("this is a $USER", &data);

	printf("%s\n", ret);
}
