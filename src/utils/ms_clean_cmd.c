/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clean_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 16:36:38 by sshakya           #+#    #+#             */
/*   Updated: 2021/08/03 16:37:06 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static void	ms_clean_node_cmd(t_node **node)
{
	int	i;

	i = 0;
	free((*node)->data->cmd);
	if ((*node)->data->args)
	{
		while ((*node)->data->args[i])
		{
			free((*node)->data->args[i]);
			i++;
		}
	}
	free((*node)->data->args);
	free((*node)->data);
}

void	ms_clean_cmd(t_node **node)
{
	int	i;

	i = 0;
	if (*node)
	{
		if ((*node)->type == NO_CMD)
			ms_clean_node_cmd(node);
		if ((*node)->type == NO_PIPE)
		{
			ms_clean_cmd(&(*node)->right);
			ms_clean_cmd(&(*node)->left);
		}
		free(*node);
	}
}
