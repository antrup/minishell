/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:06:59 by atruphem          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/07/08 18:09:15 by atruphem         ###   ########.fr       */
=======
/*   Updated: 2021/07/09 01:25:11 by sshakya          ###   ########.fr       */
>>>>>>> 42f559cd32dbf57794bb6e25058458c40da0aae6
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
		ms_lexer(&data);
#if TEST		
		print_token(&data);
<<<<<<< HEAD
		add_history(str);
		free(str);
		ms_clean(&data);
		if (!inte)
			return (0);
=======
#endif
		add_history(data.history);
		if (data.inte == 0)
			return (0);
		ms_clean(&data);
		sigaction(SIGINT, &data.sig, 0);
>>>>>>> 42f559cd32dbf57794bb6e25058458c40da0aae6
	}
	return (0);
}
