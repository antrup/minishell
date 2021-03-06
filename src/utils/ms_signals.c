/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Satcheen SHAKYA <sshakya@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:02:43 by Satcheen          #+#    #+#             */
/*   Updated: 2021/08/07 00:02:40 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_newline(int sig)
{
	(void)sig;
	if (g_shell.data->thead != NULL && g_shell.r_pid != 0)
	{
		write(0, "\n", 1);
		return ;
	}
	else
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_shell.data->thead == NULL)
			rl_redisplay();
	}
}

static void	ms_exit_main(void)
{
	write(1, "exit\n", 5);
	tcsetattr(0, TCSANOW, &g_shell.data->info.term_ios);
	ms_clean(g_shell.data);
	rl_clear_history();
	exit (1);
}

void	ms_exit_sig(int sig)
{
	int	i;

	i = EOF;
	(void)sig;
	if (g_shell.data->thead != NULL)
	{
		write(1, "Quit (core dumped)\n", 19);
		return ;
	}
	if (g_shell.rda == 1)
	{
		if (g_shell.r_pid == 0)
		{	
			close(g_shell.rda_fd[0]);
			write (0, "\n", 1);
			exit(0);
		}
	}
	else
		ms_exit_main();
}
