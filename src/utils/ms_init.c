/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:14:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/01 12:48:17 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_init_env(void)
{
//	int		i;
//	char	**new_env;
//	int		j;
//
//	i = 0;
//	while (environ[i])
//		i++;
//	new_env = malloc(sizeof(char *) * (i + 2));
//	if (!new_env)
//		return ;
//	j = 0;
//	while (j < i)
//	{
//		new_env[j] = ft_strdup(environ[j]);
//		j++;
//	}
//	new_env[i] = NULL;
//	environ = new_env;
	g_shell.env_pt = NULL;
}

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
	free(data->line);
	data->line = NULL;
}

void	ms_shell_input_io(t_ms *data)
{
	data->info.ms_input.c_cc[VQUIT] = KEY_CTRL_C;
	data->info.ms_input.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &data->info.ms_input);
}
