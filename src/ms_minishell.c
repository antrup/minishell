/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:06:59 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/09 00:39:49 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_ms	data;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		ms_init(&data);
		data.history = readline("Myshell: ");
		ms_lexer(data.history, &(data.tlist));
#if TEST		
		print_token(&data);
#endif
		add_history(data.history);
		if (data.inte == 0)
			return (0);
		ms_clean(&data);
		sigaction(SIGINT, &data.sig, 0);
	}
	return (0);
}
