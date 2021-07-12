/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_expanser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 17:29:25 by sshakya           #+#    #+#             */
/*   Updated: 2021/07/12 17:10:10 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

//char	*ms_expanser(char *word, t_ms *data);

int main(int argc, char **argv)
{
	t_ms data;
	char *ret;
	
	(void)argc;
	(void)argv;
	while (1)
	{
		ms_init(&data);
		data.history = readline("Myshell: ");
		ret = ms_expanser(data.history);
		add_history(data.history);
		printf("%s\n", ret);
		ms_clean(&data);
		sigaction(SIGINT, &data.sig, 0);
	}
}
