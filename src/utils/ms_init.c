/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:14:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/08/07 00:03:20 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ms_exp_min_env(char *pwd, char **pwd_env)
{
	ft_strlcpy(pwd_env[0], "PWD=", 5);
	ft_strlcpy(pwd_env[0] + 4, pwd, ft_strlen(pwd) + 1);
	ms_export(pwd_env);
	free(pwd_env[0]);
	pwd_env[0] = malloc(sizeof(char) * 10);
	if (!pwd_env[0])
		return (1);
	ft_strlcpy(pwd_env[0], "PATH=/bin", 10);
	ms_export(pwd_env);
	free(pwd_env[0]);
	return (0);
}

int	ms_init_env(void)
{
	char	*pwd;
	char	**pwd_env;

	if (!getenv("PWD"))
	{
		environ = NULL;
		pwd = malloc(sizeof(char) * 1000);
		if (!pwd)
			return (1);
		if (!getcwd(pwd, 1000))
			return (1);
		pwd_env = malloc(sizeof(char *) * 2);
		if (!pwd_env)
			return (1);
		pwd_env[0] = malloc(sizeof(char) * (ft_strlen(pwd) + 5));
		if (!pwd_env[0])
			return (1);
		pwd_env[1] = NULL;
		free(pwd_env);
		return (ms_exp_min_env(pwd, pwd_env));
	}
	return (0);
}

int	ms_init(t_ms *data, char **argv, char **env)
{
	if (env)
		g_shell.env = env;
	if (ms_init_env())
		return (1);
	ft_memset(data, 0, sizeof(t_ms));
	data->tokens = NULL;
	data->line = NULL;
	data->thead = NULL;
	g_shell.data = data;
	g_shell.mypath = argv[0];
	if (tcgetattr(0, &data->info.term_ios) == -1)
		return (1);
	ft_memcpy(&data->info.ms_ios, &data->info.term_ios,
		sizeof(data->info.ms_ios));
	ft_memcpy(&data->info.ms_input, &data->info.term_ios,
		sizeof(data->info.ms_ios));
	signal(SIGINT, &ms_newline);
	signal(SIGQUIT, &ms_exit_sig);
	return (0);
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
	data->info.ms_input.c_cc[VINTR] = KEY_NONE;
	data->info.ms_input.c_cc[VQUIT] = KEY_CTRL_C;
	tcsetattr(0, TCSANOW, &data->info.ms_input);
}
