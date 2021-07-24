/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:14:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/24 12:41:20 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_init(t_ms *data)
{
	ft_memset(data, 0, sizeof(t_ms));
	data->tokens = NULL;
	data->line = NULL;
	g_shell.data = data;
	g_shell.on = 1;
	tcgetattr(0, &data->info.term_ios);
	ft_memcpy(&data->info.ms_ios, &data->info.term_ios,
		sizeof(data->info.ms_ios));
}

void	ms_init_shell(t_ms *data)
{
	//data->info.inte = is_interactive();
		// FIX TO SEND NEWLINE
	data->info.ms_ios.c_cc[VEOF] = 3;
	data->info.ms_ios.c_cc[VINTR] = 4;
	data->info.ms_ios.c_cc[VQUIT] = 0;
	tcsetattr(0, TCSANOW, &data->info.ms_ios);
#if OSX
	data->info.sig.sa_flags = SA_SIGINFO;
	data->info.sig.sa_sigaction = ms_leak;
#endif
}

int	is_interactive(void)
{
	int	ret;

	ret = isatty(0);
	return (ret);
}
