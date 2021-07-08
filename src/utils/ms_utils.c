/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mn_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:14:09 by atruphem          #+#    #+#             */
/*   Updated: 2021/07/08 18:04:05 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static void	ms_leak(int sig, siginfo_t *var, void *param)
{
	(void)sig;
	(void)var;
	(void)param;
	system("leaks minishell");
	exit (0);
}

void	ms_init(t_ms *data)
{
	ft_memset(data, 0, sizeof(t_ms));
	data->tlist = NULL;
	data->sig.sa_flags = SA_SIGINFO;
	data->sig.sa_sigaction = ms_leak;
	data->inte = is_interactive();
}

void	ms_clean(t_ms *data)
{
	t_tlist	*temp;
	t_tlist	*head;

	head = data->tlist;
	while (head)
	{
		temp = head->next;
		if (head->tk.type != 1)
			free(head->tk.value);
		free(head);
		head = temp;
	}
}

int	is_interactive(void)
{
	int	ret;

	ret = isatty(0);
	return (ret);
}
