/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:19:21 by atruphem          #+#    #+#             */
/*   Updated: 2021/06/22 18:00:30 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int	ms_exec(t_node *head, int pipIN)
{
	pid_t		pid;
	int		pip[2];
	int		test;

	test = 0;
	if (!head)
		return (1);
	if (head->type == NO_CMD)
	{
		pid = fork();
		if (pid == -1)
			return (1);
	if (pid == 0)
		return (child(head->data, pipIN, 0));
	wait(NULL);
	return (0);
	}
	if (head->type == NO_PIPE)
	{	
		test = pipe(pip);
		pid = fork();
		if (test == -1 || pid == -1)
			return (-1);
		if (pid == 0)
			return (child(head->left->data, pipIN, pip[1]));
		wait(NULL);
		close(pip[1]);
		ms_exec(head->right, pip[0]);
	}
	return (0);
}	
