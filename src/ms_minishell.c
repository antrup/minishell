/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:06:59 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/06 20:03:36 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static void ms_leak(void)
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
		printf("%s\n", str);
		ms_lexer(str, &(data.tlist));
		printf("%s\n", data.tlist[0].tk.value);
		add_history(str);
		free(str);
		if (!inte)
			return (0);
	//	ms_clean(&data);
	}
	return (0);
}
