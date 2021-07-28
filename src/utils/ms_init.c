/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:14:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/28 17:08:26 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_init(t_ms *data)
{
	ft_memset(data, 0, sizeof(t_ms));
	data->tokens = NULL;
	data->line = NULL;
	data->thead = NULL;
	g_shell.data = data;
	g_shell.on = 1;
	tcgetattr(0, &data->info.term_ios);
	ft_memcpy(&data->info.ms_ios, &data->info.term_ios,
		sizeof(data->info.ms_ios));
	ft_memcpy(&data->info.ms_input, &data->info.term_ios,
		sizeof(data->info.ms_ios));
	signal(SIGINT, &ms_newline);
	signal(SIGQUIT, &ms_exit);
}

void	ms_init_shell_io(t_ms *data)
{
	data->info.ms_ios.c_cc[VEOF] = KEY_NONE;
	data->info.ms_ios.c_cc[VQUIT] = KEY_CTRL_D;
	data->info.ms_ios.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &data->info.ms_ios);
}

void	ms_shell_input_io(t_ms *data)
{
	data->info.ms_input.c_cc[VQUIT] = KEY_NONE;
	//data->info.ms_input.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &data->info.ms_input);
}
