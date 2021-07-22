/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:14:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/22 18:16:16 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

#if TEST
void	ms_init(t_ms *data)
{
	ft_memset(data, 0, sizeof(t_ms));
	data->tokens = NULL;
	data->info.inte = is_interactive();
	data->info.sig.sa_flags = SA_SIGINFO;
	data->info.sig.sa_sigaction = ms_leak;
	tcgetattr(0, &data->info.term_ios);
	ft_memcpy(&data->info.ms_ios, &data->info.term_ios, sizeof(data->info.ms_ios));
	data->info.ms_ios.c_cc[VEOF] = 3;
	data->info.ms_ios.c_cc[VINTR] = 4;
	tcsetattr(0, TCSANOW, &data->info.ms_ios);
}
#endif

#if !TEST
void	ms_init(t_ms *data)
{
	ft_memset(data, 0, sizeof(t_ms));
	data->tokens = NULL;
	data->info.inte = is_interactive();
	tcgetattr(0, &data->info.term_ios);
	ft_memcpy(&data->info.ms_ios, &data->info.term_ios, sizeof(data->info.ms_ios));
	data->info.ms_ios.c_cc[VEOF] = 3;
	data->info.ms_ios.c_cc[VINTR] = 4;
	tcsetattr(0, TCSANOW, &data->info.ms_ios);
}
#endif

int	is_interactive(void)
{
	int	ret;

	ret = isatty(0);
	return (ret);
}
