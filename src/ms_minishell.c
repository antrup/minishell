/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:06:59 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/08 18:09:15 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static void	ms_leak(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	int		inte;
	t_ms	data;

	inte = is_interactive();
	(void)argc;
	(void)argv;
	(void)env;
	atexit(ms_leak);
	while (1)
	{
		ms_init(&data);
		str = readline("Myshell: ");
		ms_lexer(str, &(data.tlist));
		print_token(&data);
		add_history(str);
		free(str);
		ms_clean(&data);
		if (!inte)
			return (0);
	}
	return (0);
}
