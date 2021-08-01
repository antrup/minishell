/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:14:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/01 20:31:00 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_init_env(void)
{
	char	*pwd;
	char	*pwd_env;
	if (!getenv("PWD"))
	{
		pwd = malloc(sizeof(char) * 1000);
		if (!pwd)
			return;
		if (!getcwd(pwd, 1000))
			return;
		pwd_env = malloc(sizeof(char) * (ft_strlen(pwd) + 5));
		if (!pwd_env)
			return;
		ft_strlcpy(pwd_env, "PWD=", 5);
		ft_strlcpy(pwd_env + 4, pwd, ft_strlen(pwd) + 1);
		ms_export(&pwd_env);
	g_shell.env_pt = NULL;
	}
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
	//data->info.ms_input.c_cc[VEOF] = KEY_CTRL_C;
	data->info.ms_input.c_cc[VINTR] = KEY_NONE;
	data->info.ms_input.c_cc[VQUIT] = KEY_CTRL_C;
	data->info.ms_input.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &data->info.ms_input);
}
