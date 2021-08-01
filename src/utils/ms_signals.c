/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Satcheen SHAKYA <sshakya@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:02:43 by Satcheen          #+#    #+#             */
/*   Updated: 2021/08/01 19:23:13 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ms_newline(int sig)
{
	(void)sig;
	if (g_shell.data->thead != NULL && !g_shell.rda)
	{
		write(0, "\n", 1);
		write(0, "@", 1);
		return ;
	}
	if (g_shell.rda == 1)
	{
		write(0, "#", 1);
		close(g_shell.rda_fd[0]);
		return (exit(0));
	}
	else 
	{
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	}
}

void	ms_exit(int sig)
{
	(void)sig;
	int	i;

	i = EOF;
	if (g_shell.data->thead != NULL)
	{
		write(1, "Quit (core dumped)\n", 19);
		return ;
	}
	if (g_shell.rda == 1)
	{
		write(0, "$", 1);
		//write(g_shell.rda_fd[0], &i, 1); 
		exit(0);
	}
	else 
	{
	write(1, "exit\n", 5);
	tcsetattr(0, TCSANOW, &g_shell.data->info.term_ios);
	ms_clean(g_shell.data);
	g_shell.on = 0;
	rl_clear_history();
	ms_clean_environ();
	exit (0);
	}
}
