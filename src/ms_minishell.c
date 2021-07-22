/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:06:59 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/23 01:23:43 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_exit(int sig)
{
	if (sig == SIGINT)
		write(1, "\b\bexit\n", 7);
	if (sig == SIGQUIT)
		write(1, "exit\n", 5);
	if (sig == SIGTERM)
		printf("test\n");
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	t_ms	data;

	(void)argc;
	(void)argv;
	(void)env;
	signal(SIGINT, &ms_exit);
	while (1)
	{
		ms_init(&data);
		data.line = readline("Myshell: ");
		ms_lexer(&data);
		ms_expanser(&data);
#if TEST		
		print_token(&data);
#endif
		ms_parser(&data);
#if TEST		
		print_tree(&data);
#endif
		add_history(data.line);
		if (data.line)
		if (data.info.inte == 0)
			return (0);
		ms_clean(&data);
#if OSX
		sigaction(SIGINT, &data.info.sig, 0);
#endif
	}
	return (0);
}
